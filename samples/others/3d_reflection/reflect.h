/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2009 Lion
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
*/






int	 InitGraphics();
void SelectDisplayContext(int context_id);
void ClearDrawingContext(int context_id);
int  DrawTriangles(GS_PACKET_TABLE *table, int context_index);

void DrawMesh(GS_PACKET_TABLE *table, int context_id);

void Iint3DGraphics(void);

void SetupLight(void);

void LoadTexture0(void);

void LoadTexture1(void);
void DrawChromeMesh(GS_PACKET_TABLE *table, int context_id);
void DrawOutline(GS_PACKET_TABLE *table, int context_id);
/*EOF*/
