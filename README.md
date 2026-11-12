PS4 Payload SDK
=================
An open source SDK for writing payloads for the PlayStation 4

# Build with docker

```bash
docker compose run --rm builder bash -c "cd libPS4 && make clean && make"
```

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

## Chain of Development

[CTurt](https://github.com/CTurt/PS4-SDK) > [IDC](https://github.com/idc/ps4-payload-sdk) > [xvortex](https://github.com/xvortex/ps4-payload-sdk) > [stooged](https://github.com/stooged/ps4-payload-sdk) > [Scene-Collective](https://github.com/Scene-Collective/ps4-payload-sdk)

## Why?

Built with existing payload in mind and to be used in the autobuild system. Hopefully this is just a stop-gap until a full featured Mira release.
