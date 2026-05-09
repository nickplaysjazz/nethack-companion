#ifndef EMBEDDED_ASSETS_H
#define EMBEDDED_ASSETS_H

#include <string>
#include <string_view>

namespace embedded_assets {
    std::string_view get_embedded_json(const std::string & filename) noexcept;
}

#endif // EMBEDDED_ASSETS_H
