#include <iostream>
#include <string>

using namespace std;


class Base64
{
private:
    static constexpr const char base64_chars[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static uint8_t index_of (char encoded_char)
    {
        for (int i = 0; i < 64; i++) {
            if (encoded_char == base64_chars[i]) return i;
        }
        return 64;
    }

public:
    static string encode (string origin)
    {
        int buf = 0;
        int buf_size = 0;
        string result;
        for (int origin_char : origin) {
            buf = (buf << 8) + origin_char;
            buf_size += 8;
            while (buf_size >= 6) {
                uint8_t base64_index = (buf >> (buf_size - 6));
                buf = buf ^ ((buf >> (buf_size - 6)) << (buf_size - 6));
                buf_size -= 6;
                result.push_back(base64_chars[base64_index]);
            }
        }
        if (buf_size > 0 && buf_size < 6) {
            uint8_t base64_index_offset = buf << (6 - buf_size);
            result.push_back(base64_chars[base64_index_offset]);
        }
        return result;
    }

    static string decode (string encoded)
    {
        unsigned buf = 0;
        unsigned buf_size = 0;
        string result;
        for (char encoded_char : encoded) {
            if (encoded_char == '=') break;
            uint8_t index = index_of(encoded_char);
            buf = (buf << 6) + index;
            buf_size += 6;
            while (buf_size >= 8) {
                result.push_back((char) (buf >> (buf_size - 8)));
                buf_size -= 8;
            }
        }
        return result;
    }
};

int main () {
    Base64 base64;
    string o = "zixiao is handsome";
    string encoded = base64.encode(o);
    string decoded = base64.decode(encoded);
    cout << decoded << endl;
    return 0;
}
