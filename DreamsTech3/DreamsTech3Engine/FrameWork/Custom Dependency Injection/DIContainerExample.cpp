/**
 * More complete example code accompanying Write Your Own Dependency Injection Container.
 * This is the most straight forward implementation of the DI container. While there is
 * slightly more boilerplate there are also more customization and documentation points.
 *
 * Author Nicolas Croad 2019
 */

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cassert>
#include <functional>
#include <memory>

#define CPP_17_LANG   201703L

#if __cplusplus >= CPP_17_LANG
 // C++17 version of DILifetime.
 // This lifetime object allocates services on the stack.
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

#else

 // C++11 version of DILifetime.
 // This lifetime object allocates services on the heap.
template <typename I, typename S>
class DILifetime {
public:
    template <typename... Args>
    DILifetime(I*& member, Args&&... args)
        : item_(new S(std::forward<Args>(args)...)),
        member_(&member)
    {
        *member_ = item_.get();
    }

    DILifetime(const DILifetime& other) = delete;
    DILifetime& operator=(const DILifetime& other) = delete;

    DILifetime(DILifetime&& other)
        : item_(std::move(other.item_)),
        member_(other.member_)
    {
        other.member_ = nullptr;
    }

    DILifetime& operator=(DILifetime&& other)
    {
        item_ = std::move(other.item_);
        member_ = other.member_;
        other.member_ = nullptr;
        return *this;
    }

    ~DILifetime() {
        if (member_)
            *member_ = nullptr;
    }

    const S& getComponent() const { return *item_; }
    S& getComponent() { return *item_; }

private:
    std::unique_ptr<S> item_;
    I** member_ = nullptr;
};
#endif

// Long form version of the DI container for this example.
class DI {
    // This interface is used for the basic example.
private:
    class DoThingPipeline* doThingPipeline_ = nullptr;

public:
    DoThingPipeline& getDoThingPipeline() const {
        assert(doThingPipeline_);
        return *doThingPipeline_;
    }

    template <typename S = DoThingPipeline>
    DILifetime<DoThingPipeline, S> installDoThingPipeline() {
        assert(!doThingPipeline_);
        return DILifetime<DoThingPipeline, S>(doThingPipeline_);
    }

    // These interfaces demonstrate de-virtualization performance.
private:
    class PowerFinder* powerFinder_ = nullptr;
    class VirtualPowerFinder* virtualPowerFinder_ = nullptr;
    class StaticPowerFinder* staticPowerFinder_ = nullptr;

public:
    // I have varied these functions in some ways. The
    // PowerFinder getter only allows const access.
    const PowerFinder& getPowerFinder() const {
        assert(powerFinder_);
        return *powerFinder_;
    }

    VirtualPowerFinder& getVirtualPowerFinder() const {
        assert(virtualPowerFinder_);
        return *virtualPowerFinder_;
    }

    StaticPowerFinder& getStaticPowerFinder() const {
        assert(staticPowerFinder_);
        return *staticPowerFinder_;
    }

    template <typename S = PowerFinder>
    DILifetime<PowerFinder, S> installPowerFinder() {
        assert(!powerFinder_);
        return DILifetime<PowerFinder, S>(powerFinder_);
    }

    // The Virtual power finder install doesn't have a default type.
    template <typename S>
    DILifetime<VirtualPowerFinder, S> installVirtualPowerFinder() {
        assert(!virtualPowerFinder_);
        return DILifetime<VirtualPowerFinder, S>(virtualPowerFinder_);
    }

    // The static power finder install will forward arguments to the constructor.
    template <typename S = StaticPowerFinder, typename... Args>
    DILifetime<StaticPowerFinder, S> installStaticPowerFinder(Args&&... args) {
        assert(!staticPowerFinder_);
        return DILifetime<StaticPowerFinder, S>(staticPowerFinder_, std::forward<Args>(args)...);
    }
};

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
    DI   container;
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