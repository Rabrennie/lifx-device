# lifx-device
> Library for creating Lifx compatible devices with Arduino compatible boards

[![Build Status](https://travis-ci.org/Rabrennie/lifx-device.svg?branch=master)](https://travis-ci.org/Rabrennie/lifx-device)


## Limitations
Lifx devices created through this library can not be added to your lifx cloud and cannot be claimed. This means that they will always show as Guest Devices in the lifx app.


## Development setup

Tests are run using docker.

```sh
docker build . -t lifx-device/test
docker run -v repo-dir:/lifx lifx-device/test /bin/sh -c "cd /lifx/; cmake CMakeLists.txt; make; ./runTests"
```

## Release History

* 0.0.1
    * Work in progress

## Meta

Rab Rennie – [@rennierab](https://twitter.com/rennierab)

Distributed under the MIT license. See ``LICENSE`` for more information.

## Contributing

1. Fork it (<https://github.com/rabrennie/lifx-device/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
