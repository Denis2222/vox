# vox

42 school project. Opengl voxel world from noise.

![ft_vox](https://github.com/Denis2222/vox/blob/master/example/ft_vox.gif?raw=true)

## Getting Started

C++ code compatible debian & osx

### Prerequisites

opengl>3 glfw3 glm assimp libnoise

```
#debian
apt-get install
          libgl-dev
          libglew-dev
          libglfw3
          libglfw3-dev
          libnoise-dev
          libglm-dev
          libgl1-mesa-dev
          libassimp-dev
          
#osx
brew install ...
```

### Installing


```
make (-j8)
```

And runing

```
./ft_vox [seed] [-f fullscreen]
```

## Built With

* g++
