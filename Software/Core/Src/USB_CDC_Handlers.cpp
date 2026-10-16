
#include "USB_CDC_Handlers.h"
#include "usb_cdc.h"
#include "uir.h"
#include "usb_cdc_common.h"

#include "etl/string.h"
#include "etl/string_view.h"
#include "etl/string_utilities.h"
#include "etl/to_string.h"
#include "etl/format_spec.h"

#include <stdint.h>

void SET_VOLTAGE(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void SET_CURRENT(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void SET_RESISTANCE(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void GET_CURRENT(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void SET_CONFIG(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void GET_CONFIG(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);
void HELP(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);


using HandlerFuncUsbCdc = void (*)(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);

struct CommandHandlerUsbCdc
{
    const char *id;
    HandlerFuncUsbCdc handler;
};

uint8_t str_inv_arg_usb_cdc[]  = "Invalid Argument\n";
uint8_t str_inv_ch_usb_cdc[]  = "Invalid Channel\n";
uint8_t str_wrong_arg_cnt_usb_cdc[] = "Wrong Argument Count\n";

etl::string<MAX_SIZE_USB_CDC_MESSAGE> response_usb_cdc;

CommandHandlerUsbCdc UsbCdcHandlers[NUMBER_OF_USB_CDC_HANDLERS] = {
    {"set_voltage", SET_VOLTAGE},
    {"set_current", SET_CURRENT},
    {"set_resistance", SET_RESISTANCE},
    {"get_current", GET_CURRENT},
    {"set_config", SET_CONFIG},
    {"get_config", GET_CONFIG},
    {"help", HELP}};

static bool parse_uint32(etl::string_view str, uint32_t &value)
{
    if (str.empty())
        return false;

    uint32_t result = 0;

    for (char c : str)
    {
        if (c < '0' || c > '9')
            return false;

        uint32_t digit = static_cast<uint32_t>(c - '0');

        // Проверка переполнения uint32_t
        if (result > (UINT32_MAX - digit) / 10)
            return false;

        result = result * 10 + digit;
    }

    value = result;
    return true;
}

enum class ParseResult
{
    Ok,
    InvalidCommand,
    InvalidArgument,
    WrongArgumentCount,
    Overflow
};

struct SetVoltageCommand
{
    uint32_t voltage_mV;
    // uint32_t channel;
};

ParseResult inline parse_set_voltage(
    etl::string_view message,
    SetVoltageCommand &command)
{
    // Ищем пробелы и выделяем 3 токенов:
    //
    // mid_point_mV

    static constexpr uint8_t number_of_tokens = 2U;

    etl::string_view tokens[number_of_tokens];

    size_t token_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= message.size(); ++i)
    {
        if (i == message.size() || message[i] == ' ' || message[i] == '\n')
        {
            if (i > start)
            {
                if (token_count >= number_of_tokens)
                    return ParseResult::WrongArgumentCount;

                tokens[token_count++] =
                    message.substr(start, i - start);
            }

            start = i + 1;
        }
    }

    if (token_count != number_of_tokens)
        return ParseResult::WrongArgumentCount;

    // Проверяем имя команды
    if (tokens[0] != "set_voltage")
        return ParseResult::InvalidCommand;

    if (!parse_uint32(tokens[1], command.voltage_mV))
        return ParseResult::InvalidArgument;

    return ParseResult::Ok;
}

void SET_VOLTAGE(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    SetVoltageCommand parsered_cmd = {};
    UsbCdcMessage msg = {};

    ParseResult state = parse_set_voltage(cmd, parsered_cmd);

    if (state == ParseResult::InvalidArgument)
    {
        msg.size = sizeof(str_inv_arg_usb_cdc);
        memcpy(msg.data, str_inv_arg_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    if (state == ParseResult::WrongArgumentCount)
    {
        msg.size = sizeof(str_wrong_arg_cnt_usb_cdc);
        memcpy(msg.data, str_wrong_arg_cnt_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    UIR::set_voltage_mV(parsered_cmd.voltage_mV);

    response_usb_cdc += "OK. Set voltage=";

    etl::to_string(parsered_cmd.voltage_mV, response_usb_cdc, true);
    response_usb_cdc += " mV\n";

    msg.size = response_usb_cdc.size();
    memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
    Usb_Cdc::send(&msg);
    response_usb_cdc.clear();

    return;
}

struct SetCurrentCommand
{
    uint32_t current_mA;
    // uint32_t channel;
};

ParseResult inline parse_set_current(
    etl::string_view message,
    SetCurrentCommand &command)
{
    // Ищем пробелы и выделяем 2 токенов:
    //
    // current_mA

    static constexpr uint8_t number_of_tokens = 2U;

    etl::string_view tokens[number_of_tokens];

    size_t token_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= message.size(); ++i)
    {
        if (i == message.size() || message[i] == ' ' || message[i] == '\n')
        {
            if (i > start)
            {
                if (token_count >= number_of_tokens)
                    return ParseResult::WrongArgumentCount;

                tokens[token_count++] =
                    message.substr(start, i - start);
            }

            start = i + 1;
        }
    }

    if (token_count != number_of_tokens)
        return ParseResult::WrongArgumentCount;

    // Проверяем имя команды
    if (tokens[0] != "set_current")
        return ParseResult::InvalidCommand;

    if (!parse_uint32(tokens[1], command.current_mA))
        return ParseResult::InvalidArgument;

    return ParseResult::Ok;
}


void SET_CURRENT(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    SetCurrentCommand parsered_cmd = {};
    UsbCdcMessage msg = {};

    ParseResult state = parse_set_current(cmd, parsered_cmd);

    if (state == ParseResult::InvalidArgument)
    {
        msg.size = sizeof(str_inv_arg_usb_cdc);
        memcpy(msg.data, str_inv_arg_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    if (state == ParseResult::WrongArgumentCount)
    {
        msg.size = sizeof(str_wrong_arg_cnt_usb_cdc);
        memcpy(msg.data, str_wrong_arg_cnt_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    UIR::set_current_mA(parsered_cmd.current_mA);

    response_usb_cdc += "OK. Set current=";

    etl::to_string(parsered_cmd.current_mA, response_usb_cdc, true);
    response_usb_cdc += " mA\n";

    msg.size = response_usb_cdc.size();
    memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
    Usb_Cdc::send(&msg);
    response_usb_cdc.clear();

    return;
}

struct SetResistanceCommand
{
    uint32_t resistance_Ohm;
    // uint32_t channel;
};

ParseResult inline parse_set_resistance(
    etl::string_view message,
    SetResistanceCommand &command)
{
    // Ищем пробелы и выделяем 2 токенов:
    //
    // resistance_Ohm

    static constexpr uint8_t number_of_tokens = 2U;

    etl::string_view tokens[number_of_tokens];

    size_t token_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= message.size(); ++i)
    {
        if (i == message.size() || message[i] == ' ' || message[i] == '\n')
        {
            if (i > start)
            {
                if (token_count >= number_of_tokens)
                    return ParseResult::WrongArgumentCount;

                tokens[token_count++] =
                    message.substr(start, i - start);
            }

            start = i + 1;
        }
    }

    if (token_count != number_of_tokens)
        return ParseResult::WrongArgumentCount;

    // Проверяем имя команды
    if (tokens[0] != "set_resistance")
        return ParseResult::InvalidCommand;

    if (!parse_uint32(tokens[1], command.resistance_Ohm))
        return ParseResult::InvalidArgument;

    return ParseResult::Ok;
}

void SET_RESISTANCE(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    SetResistanceCommand parsered_cmd = {};
    UsbCdcMessage msg = {};

    ParseResult state = parse_set_resistance(cmd, parsered_cmd);

    if (state == ParseResult::InvalidArgument)
    {
        msg.size = sizeof(str_inv_arg_usb_cdc);
        memcpy(msg.data, str_inv_arg_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    if (state == ParseResult::WrongArgumentCount)
    {
        msg.size = sizeof(str_wrong_arg_cnt_usb_cdc);
        memcpy(msg.data, str_wrong_arg_cnt_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    UIR::set_resistance_Ohm(parsered_cmd.resistance_Ohm);

    response_usb_cdc += "OK. Set resistance=";

    etl::to_string(parsered_cmd.resistance_Ohm, response_usb_cdc, true);
    response_usb_cdc += " Ohm\n";

    msg.size = response_usb_cdc.size();
    memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
    Usb_Cdc::send(&msg);
    response_usb_cdc.clear();

    return;
}

void GET_CURRENT(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    UsbCdcMessage msg = {};
    int16_t current = UIR::get_current();

    etl::to_string(current, response_usb_cdc, true);
    response_usb_cdc += " mA\n";

    msg.size = response_usb_cdc.size();
    memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
    Usb_Cdc::send(&msg);
    response_usb_cdc.clear();
    return;
}

void SET_CONFIG(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd);

struct SetConfigCommand
{
    UIR::UIR_type uir_type;
};

ParseResult inline parse_set_config(
    etl::string_view message,
    SetConfigCommand &command)
{
    // Ищем пробелы и выделяем 2 токенов:
    //
    // set_config_output
    // output_type

    uint8_t number_of_tokens = 2U;
    etl::string_view tokens[number_of_tokens];

    size_t token_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= message.size(); ++i)
    {
        if (i == message.size() || message[i] == ' ' || message[i] == '\n')
        {
            if (i > start)
            {
                if (token_count >= number_of_tokens)
                    return ParseResult::WrongArgumentCount;

                tokens[token_count++] =
                    message.substr(start, i - start);
            }

            start = i + 1;
        }
    }

    if (token_count != number_of_tokens)
        return ParseResult::WrongArgumentCount;

    // Проверяем имя команды
    if (tokens[0] != "set_config")
        return ParseResult::InvalidCommand;

    if (tokens[1] == "voltage")
    {
        command.uir_type = UIR::VOLTAGE;
        return ParseResult::Ok;
    }
    else if (tokens[1] == "current")
    {
        command.uir_type = UIR::CURRENT;
        return ParseResult::Ok;
    }else if (tokens[1] == "resistance")
    {
        command.uir_type = UIR::RESISTANCE;
        return ParseResult::Ok;
    }
    else
    {
        return ParseResult::InvalidArgument;
    }

    return ParseResult::Ok;
}

void SET_CONFIG(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    SetConfigCommand parsered_cmd = {};
    UsbCdcMessage msg = {};

    ParseResult state = parse_set_config(cmd, parsered_cmd);

    if (state == ParseResult::InvalidArgument)
    {
        msg.size = sizeof(str_inv_arg_usb_cdc);
        memcpy(msg.data, str_inv_arg_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    if (state == ParseResult::WrongArgumentCount)
    {
        msg.size = sizeof(str_wrong_arg_cnt_usb_cdc);
        memcpy(msg.data, str_wrong_arg_cnt_usb_cdc, msg.size);
        Usb_Cdc::send(&msg);
        return;
    }

    UIR::set_uir_type(parsered_cmd.uir_type);

    if (parsered_cmd.uir_type == UIR::UIR_type::VOLTAGE)
    {
        //DO::set_state_output(DO::get_state_output());

        response_usb_cdc += "OK. UIR type is VOLTAGE\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }
    else if (parsered_cmd.uir_type ==UIR::UIR_type::CURRENT)
    {
        //DO::set_freq(DO::get_freq());

        response_usb_cdc += "OK. Output type is CURRENT\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }
    else if (parsered_cmd.uir_type ==UIR::UIR_type::RESISTANCE)
    {
        //DO::set_freq(DO::get_freq());

        response_usb_cdc += "OK. Output type is RESISTANCE\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }

    return;
}


void GET_CONFIG(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    UsbCdcMessage msg = {};
    UIR::UIR_type uir_type = UIR::get_uir_type();

    if (uir_type == UIR::UIR_type::VOLTAGE)
    {
        //DO::set_state_output(DO::get_state_output());

        response_usb_cdc += "OK. UIR type is VOLTAGE\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }
    else if (uir_type ==UIR::UIR_type::CURRENT)
    {
        //DO::set_freq(DO::get_freq());

        response_usb_cdc += "OK. Output type is CURRENT\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }
    else if (uir_type ==UIR::UIR_type::RESISTANCE)
    {
        //DO::set_freq(DO::get_freq());

        response_usb_cdc += "OK. Output type is RESISTANCE\n";
        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        Usb_Cdc::send(&msg);
        response_usb_cdc.clear();

        return;
    }

    return;
}

void HELP(etl::string<MAX_SIZE_USB_CDC_MESSAGE> &cmd)
{
    UsbCdcMessage msg = {};

    for (uint8_t i = 0; i < NUMBER_OF_USB_CDC_HANDLERS - 1U; i++)
    {
        response_usb_cdc += UsbCdcHandlers[i].id;
        response_usb_cdc += "\n";

        msg.size = response_usb_cdc.size();
        memcpy(msg.data, response_usb_cdc.c_str(), msg.size);
        while (Usb_Cdc::send(&msg) != Status::OK)
            ;
        response_usb_cdc.clear();
    }

    return;
}

void UsbCdcCommmandHandler(UsbCdcMessage *usb_cdc_rx_message)
{
    etl::string<MAX_SIZE_USB_CDC_MESSAGE> str(reinterpret_cast<char *>(usb_cdc_rx_message->data), usb_cdc_rx_message->size);

    etl::string_view cmd_name;

    etl::to_lower_case(str);

    for (size_t i = 0; i <= str.size(); ++i)
    {
        if (i == str.size() || str[i] == ' ' || str[i] == '\n')
        {
            cmd_name = str.substr(0, i);
            break;
        }
    }

    for (uint8_t i = 0; i < NUMBER_OF_USB_CDC_HANDLERS; i++)
    {
        if (cmd_name.compare(reinterpret_cast<const char *>(UsbCdcHandlers[i].id)) == 0)
        {
            UsbCdcHandlers[i].handler(str);
            continue;
        }
    }
    return;
}
