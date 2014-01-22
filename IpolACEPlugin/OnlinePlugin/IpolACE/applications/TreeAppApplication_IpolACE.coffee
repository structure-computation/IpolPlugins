class TreeAppApplication_IpolACE extends TreeAppApplication
    constructor: ->
        super()
        
        @name = 'Automatic Color Enhancement'
        @powered_with = 'Ipol'
        @publication_link = 'http://www.ipol.im/pub/art/2012/g-ace/'
        @tutorial_link = 'http://youtu.be/AfCmbIf3DpA'

        _ina = ( app ) =>
            app.data.focus.get() != app.selected_canvas_inst()?[ 0 ]?.cm.view_id
            
        @actions.push
            ico: "img/IpolACE_bouton.png"
            siz: 1
            txt: "Ipol ACE"
            ina: _ina
            fun: ( evt, app ) =>
                app.undo_manager.snapshot()
                ipolLsd = @add_item_depending_selected_tree app.data, IpolACEItem

