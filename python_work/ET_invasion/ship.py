import pygame

class Ship:
    """管理ship"""
    def __init__(self, ai_game):
        """初始化"""
        #使用之前创建的屏幕对象
        self.screen = ai_game.screen
        #获取屏幕的矩形
        self.screen_rect = self.screen.get_rect()

        #加载图像并获取外接矩形
        self.image = pygame.image.load('images/ship.bmp')
        self.rect = self.image.get_rect()

        #初始位置放屏幕底部中间
        self.rect.midbottom = self.screen_rect.midbottom

        self.settings = ai_game.settings
        self.x = float(self.rect.x)

        #位移标志
        self.moving_right = False
        self.moving_left = False

    def update(self):
        """根据位移标志更新位置数据"""
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.x += self.settings.ship_speed
        if self.moving_left and self.rect.left > 0:
            self.x -= self.settings.ship_speed

        #rect.x只能存储整数，防止误差积累
        self.rect.x = self.x

    def blitme(self):
        """在指定位置绘制图像"""
        self.screen.blit(self.image, self.rect)

    def center_ship(self):
        self.rect.midbottom = self.screen_rect.midbottom
        self.x = float(self.rect.x)
