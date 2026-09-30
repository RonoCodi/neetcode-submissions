public class Solution {
    public bool hasDuplicate(int[] nums) {
        HashSet<int> hash = new HashSet<int>(nums.Length);
        foreach (int n in nums) 
        {
            if (!hash.Add(n))
            {
                return true;
            }
        }
        return false;
    }
}