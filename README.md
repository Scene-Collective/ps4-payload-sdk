PS4 Payload SDK
=================
An open source SDK for writing payloads for the PlayStation 4

## GitHub Action

The GitHub Action builds a project using the PS4 Payload SDK Docker image. It is designed to simplify building PlayStation 4 payloads in CI/CD workflows.

### Inputs

| Name           | Description                                | Required | Default |
|----------------|--------------------------------------------|----------|---------|
| `app_path`     | Relative path to the application to build  | Yes      |         |
| `build_command`| Build command to run inside the container  | No       | `make`  |

### Usage

```yaml
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout Repository
        uses: actions/checkout@v4
      - name: Build with PS4 Payload SDK
        uses: Scene-Collective/ps4-payload-sdk@v1
        with:
          app_path: path/to/your/app
          build_command: sh build.sh
```

## Local Development with Docker

The SDK is containerized with Docker, providing an x86_64 GNU toolchain suitable for both Linux and macOS (Apple Silicon / Intel) without needing to configure a local cross-compiler or modify system directories.

### 1. Build the SDK Docker Image

From the `ps4-payload-sdk` directory:

```bash
docker build --platform linux/amd64 -t ps4sdk .
```

### 2. Build a Payload

Navigate to any payload directory (e.g. `ps4-disable-updates`) and mount your source tree:

```bash
docker run --rm --platform linux/amd64 \
  -v "$PWD":/$(basename "$PWD") \
  -w /$(basename "$PWD") \
  ps4sdk make
```

> **Note for macOS Apple Silicon (M1/M2/M3/M4):** The `--platform linux/amd64` flag ensures the container runs using Rosetta 2 emulation, allowing the x86_64 GCC toolchain to emit code for the PS4's AMD Jaguar architecture (`-march=btver2`).

## Chain of Development
[CTurt](https://github.com/CTurt/PS4-SDK) > [IDC](https://github.com/idc/ps4-payload-sdk) > [xvortex](https://github.com/xvortex/ps4-payload-sdk) > [stooged](https://github.com/stooged/ps4-payload-sdk) > [Scene-Collective](https://github.com/Scene-Collective/ps4-payload-sdk)

## Why?
Built with existing payload in mind and to be used in the autobuild system. Hopefully this is just a stop-gap until a full featured Mira release.
