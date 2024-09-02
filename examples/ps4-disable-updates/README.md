Disable Updates
===
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/)](https://www.codacy.com/gh/Scene-Collective/ps4-disable-updates/dashboard)

## Synopsis
Disables firmware updates by creating dummy directories where updates are be downloaded.

For the payloads built with the most recent firmware supported visit [this repo].

## Notes
- Contribute translations for the decription in `meta.json`
- Requires being built with the [Scene Collective Payload SDK]
- Supports any firmware that the SDK supports
- **BEWARE:** Somewhere between 5.05 and 6.72 an extra check was added when checking for errors on system startup after a kernel panic. This check now deletes the blocker's directories, thus renabling updates.

[//]: #
  [Scene Collective Payload SDK]: <https://github.com/Scene-Collective/ps4-payload-sdk>
  [this repo]: <https://github.com/Scene-Collective/ps4-payload-repo>
