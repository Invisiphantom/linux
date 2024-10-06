  
内核源码版本: 6.11.2

```bash
make defconfig && make -j
python3 scripts/clang-tools/gen_compile_commands.py
make clean
```