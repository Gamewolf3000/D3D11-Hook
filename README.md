# D3D11-Hook

The purpose of this project is to create an application that gives both developers and players the chance to inspect how the rendering of D3D11 applications works, what resources are used, and how the api is utelized. It was inspired by the work of [Stefan Petersson](https://www.linkedin.com/in/stepet/) and his project known as [Triangelplockaren](https://www.youtube.com/watchv=qe079VilUJQ&feature=youtu.be). Stefan has also acted as a mentor of sort to me during this project, allowing me to discuss my findings and thoughts with him as well as providing help, tips, tricks as well as a template to start from.

## Examples

If you click the images below you will be directed to youtube videos showing the first version of the project applied on Metro 2033 and planet coaster.

[![D3D11 Viewer (Metro 2033)](http://img.youtube.com/vi/VIZ59WWoPuc/0.jpg)](http://www.youtube.com/watch?v=VIZ59WWoPuc&feature=youtu.be "D3D11 Viewer (Metro 2033)")

[![D3D11 Viewer (Planet Coaster)](http://img.youtube.com/vi/DjlQ4x9K-YA/0.jpg)](http://www.youtube.com/watch?v=DjlQ4x9K-YA "D3D11 Viewer (Planet Coaster)")

## Features

Currently the application allows for the inspection of the number of times different resources and states are set each frame in an applicaton, as well as toggling wireframe mode for specific rasterizer states. More features are planned in future versions and can be found in the next section.

## Future work

Currently the project is being rewritten to work with a different methodology. The project as it is now has to hook every single function manually and globally. While this approach works and is probably the easiest to start with, it is not practical in the long run. It requires more manual synchronization (since functions are overwritten globally and not per object) as well as being more verbose than it needs to be. The new approach will instead work by creating my own versions of all the interfaces used by D3D11 (device, devicecontext, ...) and let the original application work through them instead of the original interfaces. This way functions will be tied to actual objects and it opens up new possibilities. It does however require a decent amount of rewriting.

Other future plans for the project include (but are not limited to)
- More detailed information such as number of buffers alive
- Viewing vertexbuffers, textures, backbuffers and more
- Extraction of meshes and textures from games
- Replacing textures in games with custom ones
