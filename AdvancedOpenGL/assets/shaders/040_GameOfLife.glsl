#version 450 core

layout (local_size_x = 32, local_size_y = 32) in;

/*
layout (binding = 0) uniform bool grid[32][32];
*/

layout (std430, binding = 0) readonly buffer grid_in
{
    cell cell[];
} input_data;

layout (std430, binding = 1) buffer grid_out
{
    cell cell[];
} output_data;

bool getNeighborStatus(vec2 offset) {
    vec2 local_id = (int(gl_LocalInvocationID.x), int(gl_LocalInvocationID.y));
    vec2 neighbour_id = local_id + offset;
    
    int gridIndex = neighbour_id.x + neighbour_id.y * 32;

    return grid_in[gridIndex];
}

void main() {
    // Determine how much living neighbors there is
    int sum = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            sum += getNeighborStatus(vec2(x, y));
        }
    }

    // Set new status
    bool newStatus = false;
    if (sum == 3) {
        newStatus = true;
    }
    
    // Set changes to grid_out
    vec2 local_id = (int(gl_LocalInvocationID.x), int(gl_LocalInvocationID.y));
    int localIndex = local_id.x + local_id.y * 32;
    grid_out[localIndex] = newStatus;
}