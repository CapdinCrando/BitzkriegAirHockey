import pygame
BLACK = (0,0,0)
 
class Paddle(pygame.sprite.Sprite):
    #This class represents a car. It derives from the "Sprite" class in Pygame.
    
    def __init__(self, color, width, height):
        # Call the parent class (Sprite) constructor
        super().__init__()
        
        # Pass in the color of the car, and its x and y position, width and height.
        # Set the background color and set it to be transparent
        self.image = pygame.Surface([width, height])
        self.image.fill(BLACK)
        self.image.set_colorkey(BLACK)
 
        # Draw the paddle (a rectangle!)
        pygame.draw.rect(self.image, color, [0, 0, width, height])
        
        # Fetch the rectangle object that has the dimensions of the image.
        self.rect = self.image.get_rect()
        self.center = center = (10 // 2 , 100 // 2);
        
    def moveUp(self, pixels):
        self.rect.y -= pixels
        #Check that you are not going too far (off the screen)
        if self.rect.y < 0:
          self.rect.y = 0
          
    def moveDown(self, pixels):
        self.rect.y += pixels
        #Check that you are not going too far (off the screen)
        if self.rect.y > 400:
          self.rect.y = 400

    def rotateLeft(self, pixels, screen):
        old_center = self.center
        new_image = pygame.transform.rotate(self.image, -pixels)
        self.image = new_image
        self.rect = new_image.get_rect()
        self.center = old_center
        # drawing the rotated rectangle to the screen  
        screen.blit(new_image , self.rect)  

    def rotateRight(self, pixels, screen):
        old_center = self.center
        new_image = pygame.transform.rotate(self.image, pixels)
        self.image = new_image
        self.rect = new_image.get_rect()
        self.center = old_center
        # drawing the rotated rectangle to the screen  
        screen.blit(new_image , self.rect)  
