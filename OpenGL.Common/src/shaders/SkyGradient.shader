#shader vertex
#version 410 core

out vec2 v_uv;
void main()
{
    uint idx = gl_VertexID;
    gl_Position = vec4(idx & 1, idx >> 1, 0.0, 0.5) * 4.0 - 1.0;
    v_uv = vec2(gl_Position.xy * 0.5 + 0.5);
}


#shader fragment
#version 410 core

uniform vec4 top_color_top;
uniform vec4 top_color_mid;
uniform vec4 bot_color_mid;
uniform vec4 bot_color_bot;
in vec2 v_uv;
out vec4 frag_color;

void main()
{
    if (v_uv.y > 0.5)
    {
        frag_color = top_color_mid * ((1 - v_uv.y) * 2) + top_color_top * ((v_uv.y - 0.5) * 2);
    }
    else {
        frag_color = bot_color_bot * (abs(v_uv.y - 0.5) * 2) + bot_color_mid * (v_uv.y * 2);
    }
}