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

        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        #精确位置
        self.x = float(self.rect.x)
        self.y = float(self.rect.y)
