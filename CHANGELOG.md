# Changelog

## Unreleased


## [v0.1.0] - 2020-11-05
### Added
- First release. Device prototype.
- Added LCD1602 screen and [software interface](https://github.com/DavidAntliff/esp32-i2c-lcd1602) to control the screen.
- Added rotary encoder and implemented interface for it.
- Mechanical relay control.

## [v0.2.0] - 2020-08-02
### Added
- User can now change on and off duration and number of pulses.
- Implemented multiple properties interface.
  
### Changed
- Replaced 12V supply and 7805  with 5V supply.
- Replaced mechanical relay with solid state relay.

### Fixed
- Fixed rotary encoder and switch debounce issues.
- Project folder structure cleanup

