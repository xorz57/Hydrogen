#pragma once

#include <memory>

class Texture {
public:
    explicit Texture(const char *texturePath);
    void Bind() const;
    void Delete() const;
    [[nodiscard]] static std::shared_ptr<Texture> Create(const char *texturePath);
    static void Unbind();

private:
    std::uint32_t mID = 0;
};
