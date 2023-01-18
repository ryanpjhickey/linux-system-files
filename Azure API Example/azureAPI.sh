#!/bin/bash

# Store Azure subscription ID and resource group name in variables
SUBSCRIPTION_ID="your_subscription_id"
RESOURCE_GROUP="your_resource_group"

# Authenticate with Azure using Azure CLI
az login

# Loop through all resources in the resource group and check their status
for resource in $(az resource list --resource-group $RESOURCE_GROUP --query "[].name" -o tsv); do
  # Get the status of the current resource
  status=$(az resource show --name $resource --resource-group $RESOURCE_GROUP --query "provisioningState" -o tsv)
  echo "Resource $resource has a status of $status"
done
