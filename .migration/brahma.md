# Migration Plan: brahma

Selected: 2026-07-30. Source: `git@github.com:hariharan-devarajan/brahma.git` (develop; note — not LLNL org). Target: `ssh://git@czgitlab.llnl.gov:7999/dftracer/brahma.git` (repo exists on czgitlab, empty).

## Findings

- Local checkout on `develop`, up to date with origin.
- CI: one workflow `ci.yml` — build+test in container `hdevarajan92/brahma-ci:latest`, 4-way matrix over hdf5×mpi (`hdf5@1.8.23`/`mpich@3.4.3`, `hdf5@1.10.11`/`openmpi@4.1.6`, `hdf5@1.12.3`/`mpich@4.2.3`, `hdf5@1.14.5`/`openmpi@5.0.6`), sources `.github/workflows/scripts/load_env.sh`, cmake with BRAHMA_ENABLE_TESTING/HDF5/MPI flags, ctest.
- **No `docs/`** — author minimal Sphinx docs (intro + API from `include/brahma/*.h`: interceptor, singleton, interfaces posix/stdio/mpi/mpiio/hdf5).
- `gitlab` remote added and verified.
- Dependency: `dependency/CMakeLists.txt` fetches cpp-logger v0.0.8 from GitHub; made URL configurable so GitLab CI can pull from czgitlab mirror.

## Steps

1. [x] Fetch/pull latest `develop`
2. [x] Add + verify `gitlab` remote (dftracer group repo already exists)
3. [x] Convert `ci.yml` → `.gitlab-ci.yml`: `build-test` job, image `hdevarajan92/brahma-ci:latest`, `parallel.matrix` over the 4 hdf5/mpi combos, reuse `load_env.sh`, same cmake/ctest commands; rules on push (excluding `Merge pull request` commit messages) + MR
4. [x] Author `docs/` (conf.py, index, introduction, api, requirements.txt) — host-neutral Sphinx, RTD-compatible (falls back to alabaster)
5. [x] Add `pages` job (develop + temporary gitlab-migration rule)
6. [x] Local test: YAML parses; sphinx build succeeds; cmake configure accepts + consumes `BRAHMA_CPP_LOGGER_GIT_URL` (full matrix build not reproducible locally — needs `hdevarajan92/brahma-ci:latest` container/spack env; clone step blocked locally by network/askpass, env-only)
7. [x] Commit on `gitlab-migration`; copy `.migration/REVERT.md` + this file into repo `.migration/`
8. [x] Push `develop`, tags, `gitlab-migration` to gitlab
9. [x] Report pipeline URL: <https://czgitlab.llnl.gov/dftracer/brahma/-/pipelines>
10. [ ] User merges after green pipeline

## Executed changes (what to undo on revert)

- **Remote**: `gitlab` = `ssh://git@czgitlab.llnl.gov:7999/dftracer/brahma.git` (remove with `git remote remove gitlab`).
- **Branches pushed to gitlab**: `develop` (base of migration), `gitlab-migration` (migration commits), plus all tags.
  - Commit 1 `fd6c32d` — ci: add GitLab CI; make cpp-logger git URL configurable (`.gitlab-ci.yml` new; `dependency/CMakeLists.txt` edited)
  - Commit 2 `5e859a8` — docs: add Sphinx docs (intro + API) and GitLab Pages job (`docs/` new: conf.py, index.rst, introduction.rst, api.rst, requirements.txt)
  - Commit 3 — docs: add migration plan and revert instructions (`.migration/` copied into repo)
- **CMake dependency change — IN-PLACE, must be fixed on revert**
  (`dependency/CMakeLists.txt`): cpp-logger `fetch_package` URL changed from
  `https://github.com/LLNL/cpp-logger.git` to
  `https://lc.llnl.gov/gitlab/dftracer/cpp-logger.git` (per user request; no
  cache variable — the earlier `BRAHMA_CPP_LOGGER_GIT_URL` approach was
  removed). A `NOTE(gitlab-migration)` comment above the `GIT` line records the
  original URL. **When moving back to GitHub, restore the GitHub URL** — see
  `.migration/REVERT.md` "In-place source changes".
- **Nothing pushed to origin (GitHub)**; `.github/` untouched. To revert on
  GitLab: delete branch `gitlab-migration` (or the whole czgitlab repo
  contents); local repo left on `develop`.

## Status log

- 2026-07-30: remote added, plan created.
- 2026-07-30: `.gitlab-ci.yml` written (build-test matrix ×4 + pages job); `BRAHMA_CPP_LOGGER_GIT_URL` cache var added to `dependency/CMakeLists.txt` (default GitHub).
- 2026-07-30: cpp-logger tag verified on czgitlab: `git ls-remote ssh://.../cpp-logger.git v0.0.8` → `31753df8...`. **https ls-remote timed out from this login node** (proxy); CI uses the https URL since runners sit on the czgitlab network — watch first pipeline for clone failures and switch to a CI_JOB_TOKEN URL if needed.
- 2026-07-30: Sphinx docs authored; local tests: YAML parses (safe_load), sphinx-build succeeds, cmake configure consumes the new variable (clone attempt reached the URL; failed locally only due to askpass/network — environment, not config).
- 2026-07-30: committed on `gitlab-migration` (fd6c32d, 5e859a8, + .migration commit); pushed `develop`, tags, `gitlab-migration` to gitlab.
- 2026-07-30: Replaced BRAHMA_CPP_LOGGER_GIT_URL variable with in-place URL change to https://lc.llnl.gov/gitlab/dftracer/cpp-logger.git (user request); revert note added to REVERT.md and NOTE(gitlab-migration) comment in dependency/CMakeLists.txt.
- 2026-07-30: Dependency URL switched from https (lc.llnl.gov) to ssh form ssh://git@czgitlab.llnl.gov:7999/dftracer/cpp-logger.git (user request); verified reachable (tag v0.0.8).
- 2026-07-30: CI moved off the brahma-ci container onto LC corona batch runner (1 node) via inline .corona-batch template (tags [batch, corona], SCHEDULER_PARAMETERS -N 1 -q pdebug -t 60); 4-way hdf5×mpi spack matrix collapsed to module toolchain (gcc/11.2.1, mvapich2/2.3.7, hdf5-parallel) — noted in a comment; load_env.sh no longer used by GitLab CI (GitHub CI unchanged). Pages job on corona batch via python module + venv.
