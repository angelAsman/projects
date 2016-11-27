

import os.path, sys
import pygame
from pygame.locals import *
import numpy
import math
import os, pygame
from random import randint, random, shuffle
from math import sin, cos, pi
from time import sleep

if not pygame.image.get_extended():
    raise SystemExit("Sorry, extended image module required")

main_dir = os.path.split(os.path.abspath(__file__))[0] # Program's directory

#constants
SCREEN = Rect(0, 0, 900, 700)
screen = (900,700)
NEWBUBBLE = 30


def load_image(file):
    file = os.path.join(main_dir, 'data', file)
    try:
        surface = pygame.image.load(file)
    except pygame.error:
        raise SystemExit('Could not load image "%s" %s'%(file, pygame.get_error()))
    return surface.convert()


def imageLoader(image, scale, clip):
    asset = pygame.image.load(image)
    assetClipped = pygame.Surface((clip[2], clip[3]))
    assetClipped.blit(asset, (0,0), clip)
    return pygame.transform.scale(assetClipped, (clip[2]* scale, clip[3] * scale))
        

class Bubble(pygame.sprite.Sprite):
       
    def __init__(self, image, scale, clip, ckey, xspeed, yspeed):
        pygame.sprite.Sprite.__init__(self)
        
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.image.set_alpha(130)
        self.rect = self.image.get_rect()
        self.rect.x = 100
        self.rect.y = 100
        self.x, self.y = (randint(0,710), randint(0,510))
        self.xspeed = xspeed
        self.yspeed = yspeed
        
        
    def update(self):
        self.floater()            
                
        
    def floater(self):
        screen = pygame.display.get_surface()
        self.area = screen.get_rect()
        self.x = self.x + self.xspeed
        self.y = self.y + self.yspeed
                
        if (self.x < 0) or (self.x > 810):
            self.xspeed *= -1
        if (self.y < 0) or (self.y > 610):
            self.yspeed *= -1
        self.rect.x = self.x
        self.rect.y = self.y
      
        
    def draw(self, surface):
         surface.blit(self.image, (random.randint(0,710), random.randint(0,510)))       

class Player(pygame.sprite.Sprite):
    speed = 6
    bounce = 30
    
    def __init__(self, image, scale, clip, ckey):
        pygame.sprite.Sprite.__init__(self)
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.rect = self.image.get_rect()
        self.rect.x = 300
        self.rect.y = 200
        self.origtop = self.rect.top
        self.facing = -1
        

    def move(self, direction, vertical):
        if direction: self.facing = direction
        self.rect.move_ip(direction*self.speed, vertical*self.speed)
        self.rect = self.rect.clamp(SCREEN)
        if direction < 0:
            self.image = imageLoader("data/draw.png", 1, (110,2, 187, 102))         
            self.image.set_colorkey((0,0,0))
        elif direction > 0:
            self.image = imageLoader("data/draw.png", 1, (317, 1, 187, 102))
            self.image.set_colorkey((0,0,0))
        
        
    def draw(self, surface):
        surface.blit(self.image, (self.rect.x, self.rect.y))

        

class Shrimp(pygame.sprite.Sprite):
    
    def __init__(self, image, scale, clip, ckey):
        pygame.sprite.Sprite.__init__(self)
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.rect = self.image.get_rect()
        self.rect.x = 300
        self.rect.y = 200
        self.popping = 0

    def update(self):
        pos = pygame.mouse.get_pos()
        self.rect.midtop = pos
        if self.popping:
            self.rect.move_ip(10, 20)
             

class Shell(pygame.sprite.Sprite):
    def __init__(self, image, scale, clip, ckey, target, shrimpy):
        pygame.sprite.Sprite.__init__(self)
        self.target = target
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.rect = self.image.get_rect()
        self.rect.x = 100
        self.rect.y = 100
        
        self.shrimpy = shrimpy
        self.inside = True
                 

    def update(self):
        if self.inside:
            self.image.set_alpha(130)
            self.rect.center = self.target.rect.center
        else:       
            self.rect.y +=2
            
        
                     
    def draw(self, surface):
         surface.blit(self.image, (self.rect.x, self.rect.y))

        
        
class Clam(pygame.sprite.Sprite):
    def __init__(self, image, scale, clip, ckey, target, shrimpy):
        pygame.sprite.Sprite.__init__(self)
        self.target = target
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.rect = self.image.get_rect()
        self.rect.x = 100
        self.rect.y = 100
        
        self.shrimpy = shrimpy
        self.inside = True
               

    def update(self):
        if self.inside:
            self.image.set_alpha(130)
            self.rect.center = self.target.rect.center
        else:       
            self.rect.y +=2
        
        
    def draw(self, surface):
         surface.blit(self.image, (self.rect.x, self.rect.y))




class BlackPearl(pygame.sprite.Sprite):
    def __init__(self, image, scale, clip, ckey, target, shrimpy):
        pygame.sprite.Sprite.__init__(self)
        self.target = target
        self.image = imageLoader(image, scale, clip)
        self.image.set_colorkey(ckey)
        self.rect = self.image.get_rect()
        self.rect.x = 100
        self.rect.y = 100
        
        self.shrimpy = shrimpy
        self.inside = True
               

    def update(self):
        if self.inside:
            self.image.set_alpha(130)
            self.rect.center = self.target.rect.center
        else:       
            self.rect.y +=2
            if self.rect.y > 610:
                self.kill()
        
        
    def draw(self, surface):
         surface.blit(self.image, (self.rect.x, self.rect.y))         
       


    

    
    


def main(winstyle = 0):
    BUBBLE = 6
    pygame.init()

    winstyle = 0
    bestdepth = pygame.display.mode_ok(SCREEN.size, winstyle, 32)
    screen = pygame.display.set_mode(SCREEN.size, winstyle, bestdepth)
    pygame.mouse.set_visible(0)


    bubbList = pygame.sprite.Group()
    shellList = pygame.sprite.Group()
    all_sprites = pygame.sprite.Group()
    bubbleObjects = []
    prizeObjects = []
      
    
    #create background
    background = load_image('background.png')
    background_stretch = pygame.transform.scale(background, (900,700))
    # create player
    player = Player("data/draw.png", 1, (110,2, 187, 102), (0,0,0))
    #create shrimp
    shrimp = Shrimp("data/draw.png", 1, (335,260, 66, 80), (0,0,0))
    
    bubble_reload = NEWBUBBLE

    # Game objects
    clock = pygame.time.Clock()
    ticks = pygame.time.get_ticks()
    
   
    # create first bubbles
    for i in range(1,6):
        
        new_bubble = Bubble("data/draw.png", 1, (0,0, 90, 90), (0,0,0),float(i)/2.2 ,float(i)/2)
        new_shell =  Shell("data/draw.png", 1, (16, 108, 52, 42), (0,0,0), new_bubble, shrimp)
        new_clam =  Clam("data/draw.png", 1, (16, 150, 52, 42), (0,0,0), new_bubble, shrimp)
        new_Bpearl =  BlackPearl("data/draw.png", 1, (16, 200, 52, 42), (0,0,0), new_bubble, shrimp)
        
        prizeObjects.append(new_shell)
        prizeObjects.append(new_clam)
        prizeObjects.append(new_Bpearl)
        
        shuffle(prizeObjects)
        shellList.add(prizeObjects[0])
        bubbList.add(new_bubble)        
        all_sprites.add(new_bubble, prizeObjects[0] )
        del prizeObjects[:]


    if BUBBLE == 2: # need time delay
                
        for i in range(1,randint(1,6)):
            bubble_reload = Bubble("data/draw.png", 1, (0,0, 90, 90), (0,0,0),randint(1,3) ,randint(1,4))


            
            bubbList.add(bubble_reload)
            all_sprites.add(bubble_reload)
            BUBBLE = BUBBLE + 1


     #enemies can pop bubbles and steal prize   

    print BUBBLE

    # Main loop
    going = True
    while going:
        clock.tick(60)
                
        for event in pygame.event.get():
            if event.type == QUIT:
                going = False
            elif event.type == KEYDOWN and event.key == K_ESCAPE:
                going = False
            elif event.type == MOUSEBUTTONDOWN:
                BUBBLE = BUBBLE - 1
                for sprite in (bubbList): # n^2
                    for shell in (shellList):                   
                        if shrimp.rect.colliderect(sprite.rect):                            
                            sprite.kill()
                            
                            if BUBBLE <= 2:
                                for i in range(1,randint(1,6)):
                                    bubble_reload = Bubble("data/draw.png", 1, (0,0, 90, 90), (0,0,0),randint(1,3) ,randint(1,4))
                                    new_shelly =  Shell("data/draw.png", 1, (16, 108, 52, 42), (0,0,0), bubble_reload, shrimp)
                                    new_clamy =  Clam("data/draw.png", 1, (16, 150, 52, 42), (0,0,0), bubble_reload, shrimp)
                                    new_Bpearly =  BlackPearl("data/draw.png", 1, (16, 200, 52, 42), (0,0,0), bubble_reload, shrimp)

                                    prizeObjects.append(new_shelly)
                                    prizeObjects.append(new_clamy)
                                    prizeObjects.append(new_Bpearly)
        
                                    shuffle(prizeObjects)
                                    shellList.add(prizeObjects[0])          
                                    bubbList.add(bubble_reload)
                                    all_sprites.add(bubble_reload, prizeObjects[0])
                                    del prizeObjects[:]
                                    BUBBLE = BUBBLE + 1
                                
                            if shrimp.rect.colliderect(shell.rect):
                                shell.inside = False
                                   
                  
            
             
        #print BUBBLE    
        #Player input
        keystate = pygame.key.get_pressed()
        
        direction = keystate[K_RIGHT] - keystate[K_LEFT]
        vertical = keystate[K_DOWN] - keystate[K_UP]
        player.move(direction, vertical)

##        if bubble_reload:
##            bubble_reload = bubble_reload - 1
##        elif not int(random() * NEWBUBBLE):
##             #NEWbubble = Bubble("data/draw.png", 1, (0,0, 90, 90), (0,0,0))
##             bubble_reload = NEWBUBBLE
##             NEWbubble.draw(screen)
         
        #update sprites
        shrimp.update()
        all_sprites.update()
        
       #draw
        screen.blit(background_stretch, (0,0))
        player.draw(screen)
        #shell.draw(screen)
        all_sprites.draw(screen)
        screen.blit(shrimp.image, (shrimp.rect.x, shrimp.rect.y))
        pygame.display.flip()


    
if __name__ == '__main__':
    try:
        main()
    finally:
        pygame.quit()
