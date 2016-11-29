#include <stdint.h>
#include <stdlib.h>

#include "../include/cache.h"

// Method implementations.

// Returns the line in the set.
int cache_insert(Cache* cache, size_t set, uint32_t tag)
{
    int i, lines_per_set, line;
    PolicyCount p_count;
    PolicyCount* policy;
    std::deque<PolicyCount>* policy_deque;
    lines_per_set = cache->lines_per_set;
    switch (cache->policy)
    {
        case DIRECT_MAP:
            (cache->sets[set]).lines[0].valid = true;
            (cache->sets[set]).lines[0].tag = tag;
            return 0;
        case LRU:
            // Check if LRU list for the set is full or not.
            if (cache->sets[set].line_order->size() != lines_per_set)
            {
                // Fill first empty line.
                for (i = 0; i < lines_per_set; i++)
                {
                    if (!cache->sets[set].lines[i].valid)
                    {
                        (cache->sets[set]).lines[i].valid = true;
                        (cache->sets[set]).lines[i].tag = tag;
                        p_count.line = i;
                        cache->sets[set].line_order->push_front(p_count);
                        return i;
                    }
                }
            }
            else
            {
                policy_deque = cache->sets[set].line_order;
                // Move front element to back.
                std::rotate(policy_deque->begin(),
                        policy_deque->begin() + 1,
                        policy_deque->end());
                line = policy_deque->front().line;
                cache->sets[set].lines[line].tag = tag; // Line must also be valid in this case.
                return line;
            }
            return -1; // We should never get to this line.
        case LFU:
            // Check if LFU list for the set is full or not.
            if (cache->sets[set].line_order->size() != lines_per_set)
            {
                // Fill the first empty line.
                for (i = 0; i < lines_per_set; i++)
                {
                    (cache->sets[set]).lines[i].valid = true;
                    (cache->sets[set]).lines[i].tag = tag;
                    p_count.line = i;
                    p_count.value = 1;
                    cache->sets[set].line_order->push_back(p_count);
                    return i;
                }
            }
            else
            {
                policy_deque = cache->sets[set].line_order;
                policy = &*std::max_element(policy_deque->begin(), policy_deque->end());
                policy->value++;
                return policy->line;
            }
            return -1;
        default:
            // TODO - Fire warning message.
            return -1;
    }
}

