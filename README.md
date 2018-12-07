# DivertBox

> Kernel Packet Divert for Windows, Linux and MacOS

---

## Roadmap
Status: **On Hold / Investigate**

Currently, I'm investigating and testing existing solutions for kernel to userspace packet diversion techniques.

Particularly,

- on Windows: [WSK API](https://docs.microsoft.com/en-us/windows-hardware/drivers/network/introduction-to-winsock-kernel), [WinDivert](https://github.com/basil00/Divert)
- on Linux: [iptables](https://wiki.archlinux.org/index.php/iptables) (and [xt_bpf](https://github.com/torvalds/linux/blob/master/net/netfilter/xt_bpf.c)), [libnetfilter_queue](https://netfilter.org/projects/libnetfilter_queue/), [DPDK](https://github.com/DPDK/dpdk)
- on MacOS: [NKE](https://developer.apple.com/library/archive/documentation/Darwin/Conceptual/NKEConceptual/intro/intro.html), [NetworkExtension](https://developer.apple.com/documentation/networkextension), [pf/ipfw/ipfilter](https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/firewalls.html)

I'm planning to come up with a cross-platform and elegant solution that abstracts kernel to application packet diversion.
