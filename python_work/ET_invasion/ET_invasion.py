import sys
import pygame

from ship import Ship
from settings import Settings
pygame.FULLSCREEN
class AlienInvasion:
    """管理资源和行为"""
    def __init__(self):
        """初始化并绘制屏幕"""
        pygame.init()
        self.clock = pygame.time.Clock()
        self.settings = Settings()
        self.screen = pygame.display.set_mode(
            (self.settings.screen_width, self.settings.screen_height))
        pygame.display.set_caption("Alien Invasion")
        self.ship = Ship(self)

    def run_game(self):
        """主循环"""
        while True:
            #监听事件
            self._check_events()
            #更新位置数据
            self.ship.update()
            #更新屏幕，根据新数据重新绘制
            self._update_screen()
            #控制帧率60
            self.clock.tick(60)
    
    def _check_events(self):
        """辅助方法，通常只在类中调用，下划线打头"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self._check_keydown_events(self, event)
            elif event.type == pygame.KEYUP:
                self._check_keyup_events
                
    def _check_keydown_events(self, event):
        """按下响应"""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = True
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = True
        elif event.key == pygame.K_q:
            sys.exit()

    def _check_keyup_events(self, event):
        """松开响应"""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = False
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = False

    def _update_screen(self):
        """更新屏幕，绘制各种矩形"""
        #重新绘制屏幕
        self.screen.fill(self.settings.bg_color)
        #重新绘制ship位置
        self.ship.blitme()

        #刷新最近绘制
        pygame.display.flip()

if __name__ == '__main__':
    #实例化并运行
    ai = AlienInvasion()
    ai.run_game()
