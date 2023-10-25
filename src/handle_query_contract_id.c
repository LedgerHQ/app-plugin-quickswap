#include "quickswap_plugin.h"

void handle_query_contract_id(ethQueryContractID_t *msg) {
    const quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;

    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_ETH_FOR_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_ETH_FOR_EXACT_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_ETH:
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->version, "Swap", msg->versionLength);
            break;

        case ADD_LIQUIDITY:
        case ADD_LIQUIDITY_ETH:
            strlcpy(msg->version, "Add Liquidity", msg->versionLength);
            break;

        case REMOVE_LIQUIDITY:
        case REMOVE_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->version, "Remove Liquidity", msg->versionLength);
            break;

        default:
            PRINTF("Selector Index :%d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
