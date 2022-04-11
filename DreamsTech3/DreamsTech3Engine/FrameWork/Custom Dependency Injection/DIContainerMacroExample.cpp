/**
 * More complete example code accompanying Write Your Own Dependency Injection Container.
 * This version uses a macro to implement the DI container members.
 *
 * Author Nicolas Croad 2019
 */

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

 // Redundant include guards mark out contents of the DI container header file.
#ifndef DI_CONTAINER_H
#define DI_CONTAINER_H

#include <cassert>
#include <functional>

template <typename I, typename S>
class DILifetime {
public:
    template <typename... Args>
    DILifetime(I*& member, Args&&... args)
        : item_(std::forward<Args>(args)...),
        member_(&member)
    {
        *member_ = &item_;
    }

    DILifetime(const DILifetime& other) = delete;
    DILifetime& operator=(const DILifetime& other) = delete;
    DILifetime(const DILifetime&& other) = delete;
    DILifetime& operator=(const DILifetime&& other) = delete;

    ~DILifetime() {
        if (member_)
            *member_ = nullptr;
    }

    const S& getComponent() const { return item_; }
    S& getComponent() { return item_; }

private:
    S   item_;
    I** member_ = nullptr;
};

#define JOIN_TOKENS(token1, token2)     token1##token2

// This is used to add interfaces into the DI container.
#define DEFINE_INTERFACE(InterfaceType, interfaceName)                                           \
private:                                                                                         \
    class InterfaceType* interfaceName = nullptr;                                                \
public:                                                                                          \
    InterfaceType& JOIN_TOKENS(get, InterfaceType)() const                                       \
    {                                                                                            \
        assert(interfaceName);                                                                   \
        return *interfaceName;                                                                   \
    }                                                                                            \
    template <typename S = InterfaceType, typename... Args>                                      \
    DILifetime<InterfaceType, S> JOIN_TOKENS(install, InterfaceType)(Args&&... args)             \
    {                                                                                            \
        assert(!interfaceName);                                                                  \
        return DILifetime<InterfaceType, S>(interfaceName, std::forward<Args>( args )...);       \
    }

// Short form version of the DI container, just lists the types.
class DI {
    DEFINE_INTERFACE(DoThingPipeline, doThingPipeline_);

    DEFINE_INTERFACE(PowerFinder, powerFinder_);
    DEFINE_INTERFACE(VirtualPowerFinder, virtualPowerFinder_);
    DEFINE_INTERFACE(StaticPowerFinder, staticPowerFinder_);

    // Further contained interfaces go here...
};

#undef JOIN_TOKENS
#undef DEFINE_INTERFACE

#endif // DI_CONTAINER_H

/**
 * Simple example of using DI continer in program code and test code.
 */
class Thing { };
class ThingConfig { };

class DoThingPipeline {
public:
    virtual Thing completeDoingThing(const ThingConfig& config) {
        // Implementation details go here.
        return Thing();
    }
};

Thing makeSpecificThing(const DI& c)
{
    ThingConfig config;
    // ...
    return c.getDoThingPipeline().completeDoingThing(config);
}

// This is the test code for the simple example.
class FakeDoThingPipeline : public DoThingPipeline {
public:
    Thing completeDoingThing(const ThingConfig& thingConfig) override
    {
        completeDoingThingCalls++;
        return Thing();
    }

public:
    // Yes, this is a very simplistic mocking technique
    int completeDoingThingCalls = 0;
};

TEST_CASE("Make specific thing does the thing") {
    DI  container;
    auto doThingPipeline = container.installDoThingPipeline< FakeDoThingPipeline >();

    Thing thing = makeSpecificThing(container);
    REQUIRE(1 == doThingPipeline.getComponent().completeDoingThingCalls);
}

/**
 * This second example demonstrates the effect of de-virtualization on performance.
 */
class PowerFinder {
public:
    int calculatePower(int base, unsigned exponent) const
    {
        return exponent == 0
            ? 1
            : calculatePower(base, exponent - 1) * base;
    }
};

class VirtualPowerFinder
{
public:
    virtual int calculatePower(int base, unsigned exponent) const
    {
        return exponent == 0
            ? 1
            : calculatePower(base, exponent - 1) * base;
    }
};

class StaticPowerFinder
{
public:
    static int calculatePower(int base, unsigned exponent)
    {
        return exponent == 0
            ? 1
            : calculatePower(base, exponent - 1) * base;
    }
};

uint64_t findSquares(const DI& c)
{
    uint64_t sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += c.getPowerFinder().calculatePower(i, 2);
    return sum;
}

uint64_t findSquaresVirtual(const DI& c)
{
    uint64_t sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += c.getVirtualPowerFinder().calculatePower(i, 2);
    return sum;
}

uint64_t findSquaresStatic(const DI& c)
{
    uint64_t sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += c.getStaticPowerFinder().calculatePower(i, 2);
    return sum;
}

TEST_CASE("Devirtualization of FindSquares", "[!benchmark]")
{
    DI container;
    auto powerFinder = container.installPowerFinder();
    auto virtualPowerFinder = container.installVirtualPowerFinder<VirtualPowerFinder>();
    auto staticPowerFinder = container.installStaticPowerFinder();

    SECTION("When the return values are captured.")
    {
        uint64_t total = 0;
        BENCHMARK("No virtual function calls involved.")
        {
            total = findSquares(container);
        }

        BENCHMARK("Virtual function calls involved.")
        {
            total = findSquaresVirtual(container);
        }

        BENCHMARK("Static function calls involved.")
        {
            total = findSquaresStatic(container);
        }

        REQUIRE(total == 333283335000);
    }
    SECTION("When the return values are ignored.")
    {
        BENCHMARK("No virtual function calls involved.")
        {
            findSquares(container);
        }

        BENCHMARK("Virtual function calls involved.")
        {
            findSquaresVirtual(container);
        }

        BENCHMARK("Static function calls involved.")
        {
            findSquaresStatic(container);
        }
    }
}