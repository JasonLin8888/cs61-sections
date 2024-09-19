#include "flapmap.hh"

void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    // Add new element
    flapmap[start] = {start, duration, flapcount};
    // OR
    // sample s = {start, duration, flapcount};
    // flapmap.insert({start, s});
    }

bool has_sample(uintptr_t t) {
    // See if time is recorded in flapmap
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        if (it->first <= t && t < it->first + it->second.duration) {
            return true;
        }
    }
	return false;
}

bool sample_overlaps(uintptr_t start, size_t duration) {
    // Check if times overlap with any existing samples
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        if (start < it->first + it->second.duration && it->first < start + duration) {
            return true;
        }
    }
	return false;
}

bool can_coalesce_up(flapmap_iter it) {
    // Current iterator is not past the last element
    assert(it != flapmap.end());

    // See if there is a next element
    auto next = it;
    ++next;
    if (next != flapmap.end()) {
        // Check if the next element is next to the current element
        if (it->first + it->second.duration == next->first) {
            return true;
        }
    }
	return false;
}

void coalesce_up(flapmap_iter it) {
    // Check that we can coalesce
    assert(can_coalesce_up(it));

    // coalesce current element with next element
    auto next = it;
    ++next;
    it->second.duration += next->second.duration;
    it->second.flapcount += next->second.flapcount;
    flapmap.erase(next);
}

bool can_coalesce_down(flapmap_iter it) {
    // Check that we can coalesce (not at the beginning)
    assert(it != flapmap.begin());
    
    // Check 
    
    // coalesce current element with previous element
    auto prev = it;
    --prev;
    if (prev != flapmap.end()) {
        // Check if the previous element is next to the current element
        if (prev->first + prev->second.duration == it->first) {
            return true;
        }
    }
	return false;
}

void print_flapmap() {
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stderr, "[%zu, %zu): %zu\n", it->first, it->first + it->second.duration, it->second.flapcount);
    }
}


int main() {
	// Tests for add_sample

    // Should print nothing
    print_flapmap();
    fprintf(stderr, "\n");

    add_sample(1, 3, 1);
    add_sample(4, 3, 2);
    add_sample(8, 2, 1);
    // Should print three samples
    print_flapmap();

	// Add tests for other functions!

}