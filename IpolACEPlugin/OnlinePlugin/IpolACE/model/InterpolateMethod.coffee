#
class InterpolateMethod extends Model
    constructor: () ->
        super()

        @add_attr
            _name: "Interpolate"
            _level: new ConstrainedVal( 2, {min: 2, max: 500, div: 498})
        
        @add_attr
            level : @_level
    
    toString: () ->
        @_name.get()
    