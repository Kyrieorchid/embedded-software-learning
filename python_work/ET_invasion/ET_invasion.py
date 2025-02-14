"""
    Todo: 增加开始按钮（鼠标检测）
            增加计分、等级系统
            ...
"""
import sys
import pygame
from time import sleep

from ship import Ship
from settings import Settings
from bullet import Bullet
from alien import Alien
from game_stats import GameStats

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
        self.bullets = pygame.sprite.Group()
        self.aliens = pygame.sprite.Group()
        self._create_fleet()
        self.stats = GameStats(self)
        self.game_active = True

    def run_game(self):
        """主循环"""
        while True:
            #监听事件
            self._check_events()
            if self.game_active:
                self.ship.update()
                self._update_bullets()
                self._update_aliens()
            self._update_screen()
            #控制帧率60
            self.clock.tick(60)

    def _ship_hit(self):
        if(self.stats.ships_left > 0):
            self.stats.ships_left -= 1

            self.bullets.empty()
            self.aliens.empty()

            self._create_fleet()
            self.ship.center_ship()

            sleep(0.5)
        else:
            self.game_active = False

    def _check_fleet_edges(self):
        for alien in self.aliens.sprites():
            if(alien.check_edges()):
                for alien in self.aliens.sprites():
                    alien.y += self.settings.fleet_drop_speed
                    alien.rect.y = alien.y
                self.settings.fleet_direction *= -1
                break

    def _update_aliens(self):
        self._check_fleet_edges()
        self.aliens.update()
        self._check_ship_alien_collision()
        self._chech_aliens_bottom()

    def _check_ship_alien_collision(self):
        if pygame.sprite.spritecollideany(self.ship, self.aliens):
            self._ship_hit()

    def _update_bullets(self):
        """更新bullet位置并删除消失的bullet"""
        self.bullets.update()
        #删除已经消失的bullet，迭代对象长度不能变，这里迭代它的副本
        for bullet in self.bullets.copy():
            if bullet.rect.bottom <= 0:
                self.bullets.remove(bullet)
        #print(len(self.bullets))
        #检测碰撞
        self._check_bullet_alien_collision()
        
    def _check_bullet_alien_collision(self):
        collision = pygame.sprite.groupcollide(self.bullets, self.aliens, True, True)
        if not self.aliens:
            #alien为空，remov所有bullets
            self.bullets.empty()
            self._create_fleet

    def _chech_aliens_bottom(self):
        for alien in self.aliens.sprites():
            if(alien.rect.bottom >= self.settings.screen_height):
                self._ship_hit()
                break

    def _check_events(self):
        """辅助方法，通常只在类中调用，下划线打头"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self._check_keydown_events(event)
            elif event.type == pygame.KEYUP:
                self._check_keyup_events(event)
                
    def _check_keydown_events(self, event):
        """按下响应"""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = True
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = True
        elif event.key == pygame.K_SPACE:
            self._fire_bullet()
        elif event.key == pygame.K_q:
            sys.exit()

    def _fire_bullet(self):
        """按下空格才创建一个实例并加入group"""
        new_bullet = Bullet(self)
        self.bullets.add(new_bullet)

    def _check_keyup_events(self, event):
        """松开响应"""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = False
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = False

    def _create_alien(self, x_position, y_position):
        new_alien = Alien(self)
        new_alien.x = x_position
        new_alien.y = y_position
        new_alien.rect.x = x_position
        new_alien.rect.y = y_position
        self.aliens.add(new_alien)

    def _create_fleet(self):
        """创建alien-fleet"""
        #create an instance
        alien = Alien(self)
        alien_width = alien.rect.width
        alien_height = alien.rect.height

        current_x = alien_width
        current_y = alien_height

        while (current_y < self.settings.screen_height - 6 * alien_height):
            while (current_x < self.settings.screen_width - 2 * alien_width):
                self._create_alien(current_x, current_y)
                current_x += 2 * alien_width
            #一排排生成，这里重置x
            current_x = alien_width
            current_y += 1.5 * alien_height

    def _update_screen(self):
        """更新屏幕，绘制各种矩形"""
        #重新绘制屏幕
        self.screen.fill(self.settings.bg_color)
        #重新绘制ship和bullet位置
        #先画bullet再画ship，然后再flip刷新，防止bullet挡住ship
        for bullet in self.bullets.sprites():
            bullet.draw_bullet()
        self.ship.blitme()

        #绘制aliens
        self.aliens.draw(self.screen)

        #刷新最近绘制
        pygame.display.flip()

if __name__ == '__main__':
    #实例化并运行
    ai = AlienInvasion()
    ai.run_game()
