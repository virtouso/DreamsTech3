/**
 * More complete example code accompanying Write Your Own Dependency Injection Container.
 * This version uses multiple inheritance to implement the DI container.
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

template <typename I>
class DIMember {
private:
    class I* service_ = nullptr;

public:
    I& get() const {
        assert(service_ && "No interface of this type has been installed.");
        return *service_;
    }

    template <typename S, typename... Args>
    DILifetime<I, S> install(Args&&... args) {
        assert(!service_ && "An interface of this type was previously installed.");
        return DILifetime<I, S>(service_, std::forward<Args>(args)...);
    }
};

class DoThingPipeline;
class PowerFinder;
class VirtualPowerFinder;
class StaticPowerFinder;

/**
 * DI container using multiple inheritance to reduce boilerplate without
 * using macros.
 */
class DI : private DIMember<DoThingPipeline>,
    private DIMember<PowerFinder>,
    private DIMember<VirtualPowerFinder>,
    private DIMember<StaticPowerFinder>
    // Further contained interfaces go here...
{
public:
    template <typename I>
    I& get() const {
        return DIMember<I>::get();
    }

    template <typename I, typename S = I, typename... Args>
    DILifetime<I, S> install(Args&&... args) {
        return DIMember<I>::install<I, S>(std::forward<Args>(args)...);
    }
};

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
    return c.get< DoThingPipeline >().completeDoingThing(config);
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
    auto doThingPipeline = container.install< DoThingPipeline, FakeDoThingPipeline >();

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
        sum += c.get< PowerFinder >().calculatePower(i, 2);
    return sum;
}

uint64_t findSquaresVirtual(const DI& c)
{
    uint64_t sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += c.get< VirtualPowerFinder >().calculatePower(i, 2);
    return sum;
}

uint64_t findSquaresStatic(const DI& c)
{
    uint64_t sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += c.get< StaticPowerFinder >().calculatePower(i, 2);
    return sum;
}

TEST_CASE("Devirtualization of FindSquares", "[!benchmark]")
{
    DI   container;
    auto powerFinder = container.install< PowerFinder >();
    auto virtualPowerFinder = container.install< VirtualPowerFinder, VirtualPowerFinder >();
    auto staticPowerFinder = container.install< StaticPowerFinder >();

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