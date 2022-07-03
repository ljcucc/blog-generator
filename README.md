# Blog site generator

> Project is WIP

This is a **Web Blog site Generator** written in C, integrate with pandoc CLI. 

# Get Started

To use this, make sure you installed pandoc CLI.

```
# Copmile source code
make compile

# Run to build your site
./wbg [input-path] [output-path] [template]

# for example
./wbg '/Users/ljcucc/path/to/md' '/Users/ljcucc/path/to/public' '/Users/ljcucc/path/to/src'

# or run it by using make run

make run
```

# Credits

* cJSON: https://github.com/DaveGamble/cJSON
