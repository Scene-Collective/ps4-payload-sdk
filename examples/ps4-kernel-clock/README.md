Kernel Clock
===
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/)](https://www.codacy.com/gh/Scene-Collective/ps4-kernel-clock/dashboard)

## Synopsis
Changes the internal clock of the PS4, can be used to reactive licenses/features.

For the payloads built with the most recent firmware supported visit [this repo].

## Notes
- Contribute translations for the decription in `meta.json`
- Requires being built with the [Scene Collective Payload SDK]
- Supports any firmware that the SDK supports
- Originally created by [Zer0xFF]
- **BEWARE:** Somewhere between 5.05 and 6.72 the function used changed, this payload will ONLY zero out the clock and will no reset it. This will cause the errors with trophy times, licenses etc. This would be as if you unplugged the CMOS battery.

[//]: #
  [Scene Collective Payload SDK]: <https://github.com/Scene-Collective/ps4-payload-sdk>
  [this repo]: <https://github.com/Scene-Collective/ps4-payload-repo>
  [Zer0xFF]: <https://github.com/Zer0xFF/reactPSPLUS>
