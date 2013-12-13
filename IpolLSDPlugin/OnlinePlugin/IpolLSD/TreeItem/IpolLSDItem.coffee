#
class IpolLSDItem extends TreeItem_Computable
    constructor: ( name = "IpolLSD" ) ->
        super()

        @add_attr
            scale      : new ConstrainedVal( 1.0, { min: 0.0 } )
            sigma_coef : new ConstrainedVal( 0.6, { min: 0.0 } )
            quant      : new ConstrainedVal( 2.0, { min: 0.0 } )
            ang_th     : new ConstrainedVal(22.5, { min: 0.0, max: 180.0 } )
            log_eps    : 0.0
            density_th : new ConstrainedVal( 0.7, { min: 0.0, max: 1.0  } )
            n_bins     : new ConstrainedVal( 1  , { min:   1, max: 1024, div: 1024 } )
            #reg        : ""
            #epsfile    : ""
            #svgfile    : ""
            width      : 1.5
        
        @_name.set name
        #@_ico.set "img/scilab.png"
        @_viewable.set false
        @_computation_mode.set false
        
        @add_child new ImgSetItem 'input'
        @add_output new ImgSetItem 'output'
    
    
    accept_child: ( ch ) ->
        ch instanceof ImgItem or
        ch instanceof FileItem
        
    is_app_data: ( item ) ->
        if item instanceof TreeAppData
            return true
        else
            return false
        
    #get app.data
    get_app_data: ->
        #get app_data
        it = @get_parents_that_check @is_app_data
        return it[ 0 ]
        
    do_it: ->
        app_data = @get_app_data()
        for child in @_output[0]._children
            @_output[0].rem_child child
            app_data.delete_from_tree child
        TreeItem_Computable._do_it_rec this
    
    z_index: ->
        #

