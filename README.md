
Sample usage in .bashrc:

    function join_by { local IFS="$1"; shift; echo "$*"; }
    export PROMPT_COMMAND='PS1=$(ps1 --workspace_path="$(join_by , $(ls -d /Users/bill/programs/*))")'

PROMPT_COMMAND must be used instead of setting PS1 directly since the program needs to be
re-run every time. Putting a $(...) into PS1 directly will cause it to either be run once
if it is enclosed by "", or on every prompt if enclosed by '' but improperly handling \[ and \].
PROMPT_COMMAND solves both these issues.

workspace_path option takes a bunch of literal paths considered workspaces. The top directory will
always be displayed in the prompt followed by the last N characters of the rest of the path.

