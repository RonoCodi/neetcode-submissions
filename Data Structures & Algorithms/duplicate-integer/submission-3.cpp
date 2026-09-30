#include <vector>
#include <algorithm>
#include <limits>
#include <memory_resource>

class Solution {
public:
    bool hasDuplicate(std::vector<int>& nums) {
        const int n = nums.size();
        if (n < 2) return false;

        // 1. Find min and max (single pass, cache friendly)
        int mn = std::numeric_limits<int>::max();
        int mx = std::numeric_limits<int>::min();

        for (int x : nums) {
            mn = std::min(mn, x);
            mx = std::max(mx, x);
        }

        // 2. Range-based fast path
        const long long range = (long long)mx - mn;

        // Heuristic: ~64MB max (fits L3 comfortably)
        if (range >= 0 && range <= 50'000'000) {

            // Use PMR vector for fast allocation
            static std::pmr::monotonic_buffer_resource pool;
            std::pmr::vector<uint8_t> seen(range + 1, &pool);

            for (int x : nums) {
                uint8_t& slot = seen[x - mn];
                if (slot) return true;
                slot = 1;
            }
            return false;
        }

        // 3. Fallback: sort + adjacent check
        std::sort(nums.begin(), nums.end());
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) return true;
        }
        return false;
    }
};