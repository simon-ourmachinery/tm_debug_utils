# The Machinery Debug Utilities 

This plugin adds additional debug functionality for The Machinery projects.
It has two main component:
- The `tm_debug_utils_api` plugin
- The `symbols` executable

# Building

The Machinery build tool `tmbuild` is the easiest way to build:
- Copy `tmbuild.exe` from any [The Machinery release](https://ourmachinery.com/beta.html) into the main directory.
- Run `tmbuild.exe`.

You can also use [premake](https://premake.github.io/download.html) directly:
- Copy `premake5.exe` to the main directory.
- Run `premake5.exe` with the desired configuration (vs2019 is what I use).
- Build with your desired development environment.

# tm_debug_utils_api

This API adds the ability to query debugging information on runtime.
The most useful function in this is:
```c
tm_debug_utils_api->try_decode_hash(uint64_t hash, struct tm_temp_allocator_i *ta)
```

This allows you to quickly pass a hashed string and the function will attempt to output the string that generated the hash, 
if it could not decode the hash then it will return the hash in hex form. Example usage:

```c
TM_INIT_TEMP_ALLOCATOR(ta);
tm_shader_repository_o *repo = tm_render_graph_setup_api->shader_repository(graph_setup);
tm_shader_o *shader = tm_shader_repository_api->lookup_shader(repo, user_data.shader_hash);

if (TM_ASSERT(shader, "Unable to find shader `%s`!", tm_debug_utils_api->try_decode_hash(user_data.shader_hash, ta))) {
	// ...
}

TM_SHUTDOWN_TEMP_ALLOCATOR(ta);
```

This function doesn't actually decode the hash, instead it searches for the hash in databases generated by the `symbols` project.
By default `tm_debug_utils_api` will search for these databases itself, but a search patch can also be specified with the function:

```c
tm_debug_utils_api->add_symbol_database(const char *path)
```

# Symbols

This project creates the hash databases consumed by the `tm_debug_utils_api`.
Various command line options can be passed to change its behaviour, but the most useful configuration is:

```
symbols.exe -g -i %TM_SDK_DIR%
```

This creates a hash database at the location of `symbols.exe` (by default in `%TM_SDK_DIR%/bin`), 
it will compute the hash for any literal string it can find in the entire The Machinery SDK directory.
This command can take several seconds, but only has to be executed once, or when new literal strings are added to the project.
For more information about `symbols.exe` run the following command:

```
symbols.exe --help
```
