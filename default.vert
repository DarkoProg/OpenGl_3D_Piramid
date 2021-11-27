#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;


// Outputs the color for the Fragment Shader
out vec3 color;

// Controls the scale of the vertices
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 PV;
uniform mat4 M;
uniform mat4 Mk;
uniform vec3 col;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = PV * M * Mk * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = col;
}
