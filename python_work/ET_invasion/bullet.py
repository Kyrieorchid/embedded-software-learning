import pygame
from pygame.sprite import Sprite

class Bullet(Sprite):
    """管理bullet"""

    def __init__(self, ai_game):
        """在当前位置创建一个bullet对象"""
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings
        self.color = self.settings.bullet_color

        #创建一个矩形再移动到合适位置
        self.rect = pygame.Rect(0, 0, self.settings.bullet_width,
                                self.settings.bullet_height)
        self.rect.midtop = ai_game.ship.rect.midtop

        #浮点数存储bullet位置
        self.y = float(self.rect.y)

    def update(self):
        """更新位置"""
        self.y -= self.settings.bullet_speed
        self.rect.y = self.y

    def draw_bullet(self):
        """绘制"""
        pygame.draw.rect(self.screen, self.color, self.rect)
