# Imports the game engine
import VeriPython as RPG
import time, sys


class Dialog:
    index = 0
    done = False
    texts = [
        'Welcome to The Onyx Realm.\nI am your teacher, your personal guide in this adventure.',
        'You have 4 abilities in your disposal:\n\
        - Thor\'s Thunder (q), a lightning bolt\n\
        - Surtur\'s fire (w), a fire ball\n\
        - Heal (e), a heal that restores 50hp\n\
        - Gamma Blast (r), a powerful gamma blast',
        'Let me demonstrate..'
    ]

    sizes = [
        (380, 130),
        (330, 250),
        (165, 90)
    ]

    positions = [
        (-50, -150),
        (-50, -270),
        (-50, -100)
    ]

    @staticmethod
    def Run(x: int, y: int):
        # If the index isn't the last one
        if Dialog.index < len(Dialog.texts):
            if RPG.Widgets.Begin(RPG.WindowFlags.NoDecoration, Dialog.sizes[Dialog.index]):
                RPG.Widgets.SetWindowPosition((int(x + Dialog.positions[Dialog.index][0]), int(y + Dialog.positions[Dialog.index][1])))

                # Label
                RPG.Widgets.ColoredText(Dialog.texts[Dialog.index], 0, 255, 255, 255)

                # Next Button
                if Dialog.index < len(Dialog.texts) - 1 and RPG.Widgets.Button('Next', (80, 30)):
                    Dialog.index += 1
                elif Dialog.index == len(Dialog.texts) - 1 and RPG.Widgets.Button('Ok', (80, 30)):
                    Dialog.index += 1
                    Dialog.done = True

                RPG.Widgets.End()

class Once:
    hasRun = False

    @staticmethod
    def Reset():
        Once.hasRun = False

    @staticmethod 
    def Run(func):
        if not Once.hasRun:
            func()

        Once.hasRun = True


# Setup - Is to be ran once, sets the scene up
def Setup(scene: RPG.Scene):
    # Sets the background image
    scene.SetBackground(RPG.FindFile('../resources/Textures/Background.png'), (60, 90))

    # Sets the player at (200, 800)
    player = RPG.Player()
    player.SetSpeed(150)
    player.SetSceneWidth(scene.GetWidth())
    player.SetPosition(700, 800)
    scene.SetPlayer(player)
    scene.GetPlayer().SetFacingLeft(False)
    
    # Creates a floor, left wall and right wall
    scene.AddBounds(0, 1175, 10000, 600)
    scene.AddBounds(-60, 0, 1, 2000)
    scene.AddBounds(scene.GetWidth(), 0, 1, 2000)

    # Creates a character
    character = RPG.Character()
    character.SetSceneWidth(scene.GetWidth())
    character.SetFilename(RPG.FindFile('../resources/Textures/mage.png'))
    character.SetImageCount(7, 7)
    character.SetSize(150, 150)
    character.SetPosition(1000, 800)
    character.SetIdle([ (5, 2), (6, 2) ])
    character.SetWalking([ (0, 6), (1, 6), (2, 6), (3, 6), (4, 6), (5, 6) ])
    character.SetSpeed(150)

    # Adds the character to the scene
    scene.AddCharacter('guide', character)
    scene.GetCharacter('guide').TurnLeft()

    # Loads a font from a .ttf file
    RPG.Widgets.SetFont(RPG.FindFile('../resources/Fonts/icecube.ttf'), 38.0)    


def CreateRectangle(scene, x, y):
    # Creates a solid box
    box = RPG.Rectangle()
    box.SetFilename(RPG.FindFile('../resources/Textures/stone.jpg'))
    box.SetColor([ 255, 255, 255, 255 ])
    box.SetSize((200, 300))
    box.SetPosition(x, y)

    scene.AddRectangle('box', box)


def CreateThunder(scene, character):
    # Sets the character's cast
    thunder = RPG.Cast()
    thunder.SetAnimation([ (3, 4), (4, 4), (5, 4), (5, 4), (5, 4) ])
    thunder.SetSize(200, 100)
    thunder.SetPosition(character.GetPosition()[0], character.GetPosition()[1])
    thunder.SetFilename(RPG.FindFile('../resources/Particles/spark_05.png'))
    thunder.SetColor([ 0, 255, 255, 255 ])
    character.SetCast(thunder)


def PlayerLoop(scene: RPG.Scene, deltaTime: float):
    guide = scene.GetCharacter('guide')
    
    # Creates a rectangle
    Once.Run(lambda: CreateRectangle(scene, scene.GetPlayer().GetPosition()[0] - 500, 722))
    if scene.GetRectangle('box') != None:
        scene.GetPlayer().OnCastCollision(scene.GetRectangle('box'), lambda: scene.RemoveRectangle('box'))
    else:
        if RPG.Widgets.Begin(RPG.WindowFlags.NoDecoration, (340, 110)):
            RPG.Widgets.SetWindowPosition((guide.GetPosition()[0] - 40, guide.GetPosition()[1] - 140))
            RPG.Widgets.ColoredText('Good job. The thunder even went through', 0, 255, 255, 255)
            
            if RPG.Widgets.Button('Quit demo', (80, 30)):
                scene.Quit()

            RPG.Widgets.End()


# Run - Runs every frame
def GuideLoop(scene: RPG.Scene, deltaTime: float):    
    guide = scene.GetCharacter('guide')
    x, y = guide.GetPosition()

    if not Dialog.done:
        # Displays the dialog
        Dialog.Run(x, y)
    else:
        # Walks to x: 1500
        if guide.GetPosition()[0] < 1500:
            guide.Walk(guide.GetSpeed(), 0)
        else:
            # Stops the character from walking
            guide.Walk(0, 0)
            
            Once.Run(lambda: (CreateRectangle(scene, guide.GetPosition()[0] + 350, 722), CreateThunder(scene, guide)))

            # If the cast hits the box, remove both the cast and the box
            guide.OnCastCollision(scene.GetRectangle('box'), lambda: (guide.RemoveCast(), scene.RemoveRectangle('box')))

            # If the box has been removed
            if scene.GetRectangle('box') == None:
                if RPG.Widgets.Begin(RPG.WindowFlags.NoDecoration, (340, 130)):
                    # TODO: Get a global position instead of a relative one
                    RPG.Widgets.SetWindowPosition((guide.GetPosition()[0] - 40, guide.GetPosition()[1] - 140))
                    RPG.Widgets.ColoredText('See! That was was no match for Thor\'s thunder..', 0, 255, 255, 255)
                    RPG.Widgets.ColoredText('Now you try.', 0, 255, 255, 255)
                    
                    if RPG.Widgets.Button('Ok', (80, 30)):
                        guide.TurnLeft()
                        Once.Reset()
                        scene.Loop(lambda dt: PlayerLoop(scene, dt))

                RPG.Widgets.End()


# Main function of the script
def main():
    # Creates a new scene called Hub, the width is 2500px
    scene = RPG.Scene('Hub', 2500)
    scene.Init(lambda: Setup(scene))
    scene.Loop(lambda dt: GuideLoop(scene, dt))

if __name__ == '__main__':
    main()