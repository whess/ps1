def _local_deploy_impl(ctx):
    target = ctx.attr.target
    shell_commands = "mkdir -p %s\n" % (target)

    for src in ctx.files.srcs:
        shell_commands += "echo Copying %s to %s\n" % (src.short_path, target)
        shell_commands += "cp -R %s %s/\n" % (src.short_path, target)

    ctx.actions.write(
        output = ctx.outputs.executable,
        is_executable = True,
        content = shell_commands,
    )
    runfiles = ctx.runfiles(files = ctx.files.srcs)
    return DefaultInfo(
        executable = ctx.outputs.executable,
        runfiles = runfiles,
    )

local_deploy = rule(
    executable = True,
    implementation = _local_deploy_impl,
    attrs = {
        "srcs": attr.label_list(allow_files = True),
        "target": attr.string(doc = "Deployment directory"),
    },
)
