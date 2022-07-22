# DVIC_IIM_GROUPE_P-TANK


Description du projet :

Nous avons choisi de créer un tank. Sobrement intitulé p-Tank, un jeu de mots en référence au fameux sport convivial avec des boules.

Notre Tank miniature, propose différentes fonctionnalités. Grâce à un récepteur Bluetooth, P-Tank peut être controllé à distance via une application sur smartphone. C'est le mode manuel. Les deux moteurs présents à l'intérieur du châssis permettent à P-Tank d'avancer, de reculer, et de tourner à droite et à gauche.

Nous avons ensuite décidé d'intégrer un mode automatique. L'enjeu ici était de permettre à P-Tank d'avancer automatiquement. Mais un souci se présentait à nous : en cas d'obstacles, P-Tank était malheureusement bloqué.

C'est pourquoi nous avons intégré un capteur et récepteur à ultrason permettant de détecter les obstacles. En fonction de la distance séparant l'obstacle de notre appareil de guerre, des diodes vertes, oranges et rouge s'allument.

Le mode automatique permet à pétanque de tourner seul, afin d'éviter ces obstacles.

Ainsi, tel un robot intelligent, P-Tank peut se mouvoir seul dans son espace, de façon parfaitement autonome.


Pour concevoir cet ambitieux projet, nous avons pu compter sur une équipe des plus compétente.

Margaux Malsch, **Nicolas Mopin, Sacha Le Bras, Sacha Galeuzzi, Ahmed-jibril Ait Ouaret, Ayoub El Guendouz et Hugo Boudalier** ont travaillé sur les différentes fonctions offertes par P-Tank.


Nous sommes aujourd'hui très fiers de P-Tank. Mais avec un peu plus de temps, nous aurions pu encore l'améliorer. Nous aurions par exemple aimer intégrer un Klaxon, ou encore un système permettant de lancer des projectiles. P-Tank, aurait pu être non seulement un véhicule pouvant se déplacer intelligemment, mais aussi une véritable machine de guerre.


Matériel utilisé : un châssis en deux parties, avec le bas, comprennant des roues, et des chenilles, et le capot. Ces éléments proviennent d'une impression en 3D. A l'intérieur, deux moteurs sont reliés à une carte moteur, et à un ESP-32.

l'ESP-32 est également relié au récepteur/emmeteur ultrason, permettant d'allumer les trois diodes : verte, jaune, rouge.

Les branchements sont assurés à l'aide de câbles mâles et femelles.  
