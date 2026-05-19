/*
    《两数之和》

*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        // 定义哈希表
        // key->数组元素值，value->数组下标
        unordered_map<int, int> valToIndex;

        // 遍历原数组
        for (int i = 0; i < nums.size(); i++)
        {
            // 计算需要的补数
            int need = target - nums[i];

            // 在哈希表中查找补数
            if (valToIndex.find(need) != valToIndex.end())
            {
                // 如果有，返回补数的下标+当前元素的下标
                return {valToIndex[need], i};
            }
            else
            {
                // 如果没有，把当前元素的值和下标存入哈希表
                valToIndex[nums[i]] = i;
            }
        }

        // 如果没有找到，返回空数组
        return {};
    }
};
