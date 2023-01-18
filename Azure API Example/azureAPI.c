#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Replace with your Azure subscription ID and resource group name
#define SUBSCRIPTION_ID "your_subscription_id"
#define RESOURCE_GROUP "your_resource_group"

int main() {
    // Store the command to be executed in a string
    char command[256];
    sprintf(command, "az login");
    // Execute the command to authenticate with Azure
    system(command);

    // Loop through all resources in the resource group and check their status
    sprintf(command, "az resource list --resource-group %s --query \"[].name\" -o tsv", RESOURCE_GROUP);
    FILE *fp = popen(command, "r");
    char resource[256];
    while (fgets(resource, sizeof(resource), fp) != NULL) {
        // Remove newline character from the end of the resource name
        resource[strcspn(resource, "\n")] = 0;
        // Get the status of the current resource
        sprintf(command, "az resource show --name %s --resource-group %s --query \"provisioningState\" -o tsv", resource, RESOURCE_GROUP);
        fp = popen(command, "r");
        char status[256];
        fgets(status, sizeof(status), fp);
        status[strcspn(status, "\n")] = 0;
        // Print the status of the resource
        printf("Resource %s has a status of %s\n", resource, status);
        pclose(fp);
    }
    pclose(fp);
    return 0;
}
