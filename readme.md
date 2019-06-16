# gitrolex

Time tracking based on your git branching

## CLI

The `gitrolex` CLI offers various tasks:

1. `gitrolex track feature-branch-name`: Starts tracking on `feature-branch-name`. This command is intended to be integrated into git work flows via a hook. For example, `git checkout -b my-feature-branch` would invoke `gitrolex track my-feature-branch`.

1. `gitrolex pause`: Pauses time tracking on the last tracked task (only valid if tracking has been started with `gitrolex track | play`)

1. `gitrolex play`: Resume the last paused task (only valid after calling `gitrolex pause`)

1. `gitrolex export`: Export your timesheet to some great format that everyone agrees on.
