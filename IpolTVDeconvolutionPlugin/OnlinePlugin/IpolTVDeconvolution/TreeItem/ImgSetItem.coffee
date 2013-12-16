#
class ImgSetItem extends TreeItem
    constructor: (name = 'ImgSetItem')->
        super()
        
        @_name.set name
        
    accept_child: ( ch ) ->
        #ch instanceof ImgSetItem or
        ch instanceof ImgItem or
        ch instanceof FileItem