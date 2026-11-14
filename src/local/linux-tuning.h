#ifndef LOCAL_LINUX_TUNING_H_
#define LOCAL_LINUX_TUNING_H_

// Branch kyty-otimizacao: Linux/RADV experiments, each one behind an environment variable and off unless it is set.
//   KYTY_TIMER_SLACK_NS=<n>     the process' timer slack (the kernel's default is 50000 ns): sleeps wake closer to their time
//   KYTY_UPLOAD_NICE=<-20..-1>  the upload worker's nice value (Windows raises that thread above the game's)
//   KYTY_BACKGROUND_BATCH=1     background workers (pipeline compiles) under SCHED_BATCH besides nice 10
//   KYTY_LOCK_SPINS=<n>         pauses a contended lock spins before it blocks (default 4000; common/threads.cpp)
//   KYTY_MEMORY_PRIORITY=1      VK_EXT_memory_priority and pageable device-local memory: render targets and depth first
//   KYTY_GUEST_HUGEPAGES=1      MADV_HUGEPAGE on the direct memory's shared mappings (shmem THP "advise")
//   KYTY_GUEST_DONTDUMP=1       MADV_DONTDUMP on them: a core dump leaves the guest's memory out
//   KYTY_SWAPCHAIN_IMAGES=<n>   swapchain images asked for (default: the surface's minimum + 1)
//   KYTY_PRESENT_WAIT=1         VK_KHR_present_wait: a present waits for the one before it to be shown (not with FSR's
//                               frame generation swapchain)
//   KYTY_HDR_METADATA=<nits>    VK_EXT_hdr_metadata on the HDR10 swapchain: BT.2020, the display's peak in nits (not with
//                               FSR's frame generation swapchain)

#include <cstdlib>

namespace LinuxTuning {

inline long Value(const char* name, long unset) {
	const char* text = std::getenv(name);
	return text != nullptr && *text != '\0' ? std::strtol(text, nullptr, 10) : unset;
}

inline bool On(const char* name) {
	return Value(name, 0) != 0;
}

} // namespace LinuxTuning

#endif
