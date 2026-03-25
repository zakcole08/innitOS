# innitOS
Minimal operating system built on the Linux kernel with a custom shell. Focused on programmer's and the C language

# Todo

- [x] Make scripts more robust and customisable
- [ ] Add C shell with JIT compilation and builtin commands
- [ ] Support different architecures e.g. ARM64
- [ ] Prettify
- [ ] Support networking
- [ ] Package management

# Requirements

1. Existing linux kernel [kernel.org]()
2. QEMU [https://www.qemu.org/download/#linux]()

# Installation

1. Clone the repo
```bash
git clone https://github.com/zakcole08/innitOS
```
2. Run the build script
```bash
cd innitOS
./build.sh
```
3. Start the VM - this will use your current linux kernel by default
```bash
sudo ./run.sh #<optional: /path/to/kernel/vmlinuz>
```
