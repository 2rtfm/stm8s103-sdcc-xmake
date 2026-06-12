set_plat("cross")
set_toolchains("sdcc")
set_arch("stm8")
add_rules("plugin.compile_commands.autoupdate")

local mcu_model = "STM8S103"

add_defines(mcu_model)

add_cflags("--std-sdcc2y", "--fsigned-char", "--opt-code-size")

target("libstm8s103splsplit")
  set_kind("static")
  add_files("lib/spl_split/src/*/*.c")
  add_includedirs("lib/spl_split/inc", { public = true })
  add_includedirs("conf", { public = true })

-- target("libstm8s103spl")
--   set_kind("static")
--   add_files("lib/spl/src/*.c")
--   add_includedirs("lib/spl/inc", { public = true })
--   add_includedirs("conf", { public = true })

target("libstm8it")
  set_kind("static")
  add_deps("libstm8s103splsplit")
  add_files("lib/it/src/*.c")
  add_includedirs("lib/it/inc", { public = true })

target("libmystm8")
  set_kind("static")
  -- add_deps("libstm8s103spl")
  add_deps("libstm8s103splsplit")
  add_files("src/*.c")
  add_includedirs("inc", { public = true })

local bin_name = "output"
local bin_path = "$(builddir)/cross/stm8/release/"

target(bin_name)
  set_kind("binary")
  add_deps("libmystm8")
  add_files("usr/main.c")
  set_extension(".ihx")
  after_build( function (target)
    local ihx_file = io.open(target:targetfile(), "r")
    if ihx_file then
      local bytes_len = 0
      for line in ihx_file:lines() do
        ---@cast line string
        local reclen = tonumber(line:sub(2, 3), 16) or 0
        bytes_len = reclen + bytes_len
      end
      ihx_file:close()
      print("Total bytes: ", bytes_len)
    end
  end)
  after_clean( function (target)
    os.rm(bin_path .. bin_name .. ".*")
  end)
