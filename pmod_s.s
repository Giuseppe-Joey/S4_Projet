/************************************
 * Name :     pmod.s
 * Author:    Jp Gouin
 * Version :  h2022
 ************************************/

.set noreorder  
    
.data
   
.text

.global pmod_s
# début de la fonction
.ent pmod_s
pmod_s:			# Étiquette de la fonction
    # Code à écrire
    
    jr $ra		# Retour à la fonction
    nop			# delay slot
# fin de la fonction   
.end pmod_s