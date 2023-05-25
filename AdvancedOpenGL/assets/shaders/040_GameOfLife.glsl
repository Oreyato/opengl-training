#version 450 core

layout (local_size_x = 32, local_size_y = 32) in;

/*
layout (binding = 0) uniform bool grid[32][32];
*/

layout (std430, binding = 0) buffer grid_in
{
    bool cell[];
} input_data;

layout (std430, binding = 1) buffer grid_out
{
    bool cell[];
} output_data;

bool getNeighborStatus(const ivec2 local_idP, ivec2 offset) {
    ivec2 neighbour_id = local_idP + offset;
    
    int gridIndex = neighbour_id.x + neighbour_id.y * 32;

    return input_data.cell[gridIndex];
}

void main() {
    // Get local id
    const ivec2 local_id = ivec2(gl_LocalInvocationID.x, gl_LocalInvocationID.y);
    // Get local index
    const int localIndex = local_id.x + local_id.y * 32;

    // Determine how much living neighbors there is
    int sum = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            sum += int(getNeighborStatus(local_id, ivec2(x, y)));
        }
    }

    // Set new status
    bool newStatus = false;
    if (sum == 3) {
        newStatus = true;
    } else if (sum == 2) {
        newStatus = input_data.cell[localIndex];
    }
    
    // Set changes to grid_out
    output_data.cell[localIndex] = newStatus;
}