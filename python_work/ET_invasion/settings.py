class Settings:
    """存储所有设置"""
    def __init__(self):
        """初始化设置"""
        #屏幕和ship设置
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (230, 230, 230)
        self.ship_speed = 2
        #子弹设置
        self.bullet_speed = 4
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = (60, 60, 60)
        #alien移动速度
        self.alien_speed = 5
        self.fleet_drop_speed = 30
        self.fleet_direction = 1
        
        self.ships_limit = 1
