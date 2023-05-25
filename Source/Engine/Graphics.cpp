#include "Graphics.h"
#include "Primitives.h"
#include <SDL.h>

Graphics::Graphics()
{
	SDL_Init(SDL_INIT_VIDEO);
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Graphics::CreateWindow(const char* title, int width, int height, float size)
{
    m_width = width;
    m_height = height;

    float ratio = m_width / (float)m_height;
    m_extents = glm::vec2{ size * ratio, size };

    m_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

   m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}

void Graphics::Clear()
{
    SDL_RenderClear(m_renderer);
}

void Graphics::Present()
{
    SDL_RenderPresent(m_renderer);
}

void Graphics::SetColor(const glm::vec4& color)
{
    glm::ivec4 icolor;
    icolor.r = (int)(color.r * 255);
    icolor.g = (int)(color.g * 255);
    icolor.b = (int)(color.b * 255);
    icolor.a = (int)(color.a * 255);

    SDL_SetRenderDrawColor(m_renderer, icolor.r, icolor.g, icolor.b, icolor.a);
}

void Graphics::DrawPoint(const glm::ivec2& point, const glm::vec4& color)
{
    SetColor(color);
    SDL_RenderDrawPoint(m_renderer, point.x, point.y);
}

void Graphics::DrawLine(const glm::ivec2& start, const glm::ivec2& end, const glm::vec4& color)
{
    SetColor(color);
    SDL_RenderDrawLine(m_renderer, start.x, start.y, end.x, end.y);
}

void Graphics::DrawCircle(const glm::ivec2& point, int radius, const glm::vec4& color)
{
    SetColor(color);
    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    while (x <= y) {
        SDL_RenderDrawPoint(m_renderer, point.x + x, point.y + y);
        SDL_RenderDrawPoint(m_renderer, point.x + y, point.y + x);
        SDL_RenderDrawPoint(m_renderer, point.x + y, point.y - x);
        SDL_RenderDrawPoint(m_renderer, point.x + x, point.y - y);
        SDL_RenderDrawPoint(m_renderer, point.x - x, point.y - y);
        SDL_RenderDrawPoint(m_renderer, point.x - y, point.y - x);
        SDL_RenderDrawPoint(m_renderer, point.x - y, point.y + x);
        SDL_RenderDrawPoint(m_renderer, point.x - x, point.y + y);

        if (d < 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
void Graphics::DrawFilledCircle(const glm::ivec2& point, int radius, const glm::vec4& color)
{
    // Set the color
    SetColor(color);

    // Compute the center and the squared radius
    int x0 = point.x;
    int y0 = point.y;
    int r2 = radius * radius;

    // Scanline fill the circle
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= r2) {
                SDL_RenderDrawPoint(m_renderer, x0 + x, y0 + y);
            }
        }
    }
}

glm::ivec4 Graphics::ConvertColor(const glm::vec4& color)
{
    return glm::ivec4();
}

glm::vec2 Graphics::ScreenToWorld(const glm::ivec2& screen)
{
    float x = screen.x / (float)m_width; // screen x (0 - 800) -> x (0 - 1)
    float y = (m_height - screen.y) / (float)m_height; // screen y (0 - 600) -> (0 - 1) flip

    glm::vec2 world;
    world.x = ((1 - x) * -m_extents.x) + (x * m_extents.x);
    world.y = ((1 - y) * -m_extents.y) + (y * m_extents.y);

    return world;
}

glm::ivec2 Graphics::WorldToScreen(const glm::vec2& world)
{
    float x = (world.x + m_extents.x) / (m_extents.x * 2); // world.x = 0 -> (0 + 6.66) / 13.33 -> 0.5
    float y = (world.y + m_extents.y) / (m_extents.y * 2); // world.y = 0 -> (0 + 5) / 10 = 0.5

    glm::vec2 screen;
    screen.x = x * m_width;
    screen.y = (1.0f - y) * m_height;

    return screen;
}

int Graphics::WorldToPixels(float world)
{
    return (int)(world * (m_height / (m_extents.y * 2)));
}
