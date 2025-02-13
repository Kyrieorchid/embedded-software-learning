import pygame
from pygame.sprite import Sprite

class Alien(Sprite):
    """管理alien"""

    def __init__(self, ai_game):
        super().__init__()
        self.screen = ai_game.screen
        #加载图像获取矩形
        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect()
        #位置
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height
        #精确位置，减小误差传递
        self.x = float(self.rect.x)
        self.y = float(self.rect.y)
        self.settings = ai_game.settings

    def check_edges(self):
        """检查是否触碰到边缘"""
        self_rect = self.screen.get_rect()
        #单个alien碰到右边或者左边
        return (self.rect.right >= self_rect.right) or (self.rect.left <= 0)

    def update(self):
        """move right"""
        self.x += self.settings.alien_speed * self.settings.fleet_direction
        self.rect.x = self.x
