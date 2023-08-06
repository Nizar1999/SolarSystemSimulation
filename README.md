<p align="center">  <img src="https://github.com/Nizar1999/SolarSystemSimulation/blob/master/screenshots/banner.png" width = 55%; height=55% />
</p>

![Languages](https://img.shields.io/badge/-C++-9ADFB0?style=for-the-badge&logo=cplusplus)
![Languages](https://img.shields.io/badge/-OpenGL-9ADFB0?style=for-the-badge&logo=OpenGL) 

## Motivation

Mess around with OpenGL and Dear ImGui and make a cool rendering project

## Showcase

![screen-gif](./screenshots/preview.gif)

## Features

### Configuration Menu
Ability to configure various properties of rendering, camera, and orbit

![screen-gif](./screenshots/debug.gif)

### Light Effects
Ambient + Diffuse

![screen-gif](./screenshots/lights.gif)

### Skybox
Milky way skybox so it feels spacy (actual word btw)

![screen-gif](./screenshots/skybox.gif)

### Uses Kepler's Equation to Calculate Orbital Position
Planets have different orbital parameters that are used to calculate their orbital position at a certain point in time

### Easy Configuration:
Properties of different celestial bodies can be configured easily using the config.json file

```
"Earth": {
  "orbitParameters": {
  "semiMajorAxis": 1.000,
  "eccentricity": 0.0167,
  "inclination": 0.000,
  "longitudeOfAscendingNode": -11.260,
  "argumentOfPeriapsis": 114.207
  },
  "scale": 1.000,
  "texture": "./resources/textures/earth.jpg",
  "position": {
  "x": -1.000,
  "y": 0.0,
  "z": 0.0
  }
},
```

## External Resources Used
[nlohmann json](https://github.com/nlohmann/json) - Parsing JSON

[Dear IMGUI](https://github.com/ocornut/img) - GUI Library

[STB Image](https://github.com/ocornut/img) - Loading Images

[Planet Pixel Emporium](https://planetpixelemporium.com) - Planet Textures

## Future Work
Refactor some elements of the code marked with //TODO
