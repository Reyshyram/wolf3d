#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D u_textures;
uniform vec2 u_resolution;
uniform vec2 u_player_pos;
uniform vec2 u_ray_dir_left;
uniform vec2 u_ray_dir_right;
uniform float u_horizon_y;
uniform float u_plane_dist;
uniform vec2 u_textures_size;
uniform float u_tile_size;
uniform float u_floor_index;
uniform float u_ceil_index;

vec4 sample_floor_ceil(vec2 frag) {
    float is_ceil = step(frag.y, u_horizon_y);
    float offset_to_horizon = frag.y - u_horizon_y;
    float abs_offset_to_horizon = max(abs(offset_to_horizon), 1.0);
    float camera_vertical_pos = 0.5 * u_plane_dist;
    float row_dist = camera_vertical_pos / abs_offset_to_horizon;

    float camera_x = frag.x / u_resolution.x;
    vec2 ray_dir = mix(u_ray_dir_left, u_ray_dir_right, camera_x);
    vec2 world_pos = u_player_pos + ray_dir * row_dist;

    vec2 tile_uv = fract(world_pos);
    float tile_index = mix(u_floor_index, u_ceil_index, is_ceil);

    float tiles_per_row = u_textures_size.x / u_tile_size;
    float tile_x = mod(tile_index, tiles_per_row);
    float tile_y = floor(tile_index / tiles_per_row);

    vec2 textures_uv = (vec2(tile_x, tile_y) * u_tile_size + tile_uv * u_tile_size) / u_textures_size;

    return texture2D(u_textures, textures_uv);
}

void main() {
    vec2 frag = gl_FragCoord.xy;
    vec4 color = sample_floor_ceil(frag + vec2(-0.25, -0.25));
    color += sample_floor_ceil(frag + vec2(0.25, -0.25));
    color += sample_floor_ceil(frag + vec2(-0.25, 0.25));
    color += sample_floor_ceil(frag + vec2(0.25, 0.25));
    gl_FragColor = color * 0.25;
}
