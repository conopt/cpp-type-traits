#include "type_traits.h"

// Unit Tests

#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

static_assert(Hashable<int>, "should be hashable");
static_assert(Hashable<char>, "should be hashable");
static_assert(Hashable<bool>, "should be hashable");
static_assert(Hashable<std::vector<bool>>, "should be hashable");
static_assert(Hashable<std::string>, "should be hashable");
static_assert(Hashable<std::unique_ptr<int>>, "should be hashable");

static_assert(!Hashable<std::vector<int>>, "should not be hashable");
static_assert(!Hashable<std::map<int, int>>, "should not be hashable");
static_assert(!Hashable<std::set<int>>, "should not be hashable");

static_assert(HasLess<int>, "should has <");

static_assert(InstanceOf<std::map<int,int>, std::map>, "true");
static_assert(InstanceOf<std::unordered_map<std::vector<bool>,int>, std::unordered_map>, "true");

static_assert(!InstanceOf<std::vector<int>, std::map>, "false");
static_assert(!InstanceOf<std::map<int,int>, std::unordered_map>, "false");
static_assert(!InstanceOf<std::unordered_map<int,int>, std::map>, "false");

int main()
{
}
